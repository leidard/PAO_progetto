#include "io.hpp"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QtGlobal>
#include <string>
#include <QTextStream>

#include "aquarius.hpp"
#include "sardina.hpp"
#include "tonno.hpp"
#include "phytoplankton.hpp"

IO::FileStructureError::FileStructureError(const std::string& _msg) : msg(_msg) {}

std::string IO::FileStructureError::getMsg() const { return "[JSON IOError]: " + msg; }

IO::MissingProperty::MissingProperty(std::string propertyname, std::string object) : FileStructureError("Missing Property: [" + propertyname + "] " + ((object != "") ? "in object: " + object : "")) {}

const std::string IO::DEFAULT_FILENAME = "aquarius.json";

void IO::load(Aquarius* a, const std::string& filename) const {
    QFile file(filename.c_str());
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString val = file.readAll();
    file.close();
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    if (!d.isObject()) throw FileStructureError("Root must be an Object");
    QJsonObject obj = d.object();

    if (!obj.value("name").isString()) throw MissingProperty("name");
    if (!obj.value("organismi").isArray()) throw MissingProperty("organismi");
    if (!obj.value("width").isDouble()) throw MissingProperty("width");
    if (!obj.value("height").isDouble()) throw MissingProperty("height");

    a->setName(obj.value("name").toString().toStdString());
    a->setSize(obj.value("width").toDouble(), obj.value("height").toDouble());

    auto arr = obj.value("organismi").toArray();
    for (auto it = arr.begin(); it < arr.end(); it++) {
        auto i = *it;
        try {
            a->addOrganismo(parseOrganismo(i));
        }
        catch (FileStructureError& err) {
            std::cerr << err.getMsg();
        }
    }
}

void IO::save(Aquarius* a, const std::string& filename) const {
    auto asda = filename;

    QJsonObject obj;
    obj.insert("name", a->getName().c_str());
    obj.insert("width", (int)a->getWidth());
    obj.insert("height", (int)a->getHeight());
    QJsonArray organismi;

    for (auto& o : a->getAllOrganismi()) {
        if (Tonno* tonno = dynamic_cast<Tonno*>(&*o)) {
            organismi.push_back(IO::serialize(*tonno));
        }
        else if (Sardina* sardina = dynamic_cast<Sardina*>(&*o)) {
            organismi.push_back(IO::serialize(*sardina));
        }
        else if (Phytoplankton* phyto = dynamic_cast<Phytoplankton*>(&*o)) {
            organismi.push_back(IO::serialize(*phyto));
        }
    }

    obj.insert("organismi", organismi);

    QJsonDocument doc(obj);

    QFile file(filename.c_str());
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        stream << doc.toJson().data();
    }
    file.close();
}

QJsonObject IO::serialize(const Tonno& t) {
    QJsonObject obj;
    obj.insert("type", "TONNO");
    obj.insert("position", IO::serialize(t.getPosition()));
    obj.insert("name", t.getName().c_str());

    return obj;
}

QJsonObject IO::serialize(const Sardina& s) {
    QJsonObject obj;
    obj.insert("type", "SARDINA");
    obj.insert("position", IO::serialize(s.getPosition()));
    obj.insert("name", s.getName().c_str());

    return obj;
}

QJsonObject IO::serialize(const Phytoplankton& s) {
    QJsonObject obj;
    obj.insert("type", "PHYTOPLANKTON");
    obj.insert("position", IO::serialize(s.getPosition()));
    obj.insert("name", s.getName().c_str());

    return obj;
}

QJsonObject IO::serialize(const Vect2D& v) {
    QJsonObject obj;
    obj.insert("x", v.x());
    obj.insert("y", v.y());
    return obj;
}

Vect2D IO::parseVect2D(const QJsonValue& v) {
    if (!v.isObject()) throw new FileStructureError("Expected JSON Object while parsing Organismo");
    QJsonObject obj = v.toObject();

    QJsonValue x = obj.value("x");
    if (!x.isDouble()) throw new MissingProperty("y", "Vect2D");
    QJsonValue y = obj.value("y");
    if (!y.isDouble()) throw new MissingProperty("y", "Vect2D");

    return Vect2D(x.toDouble(), y.toDouble());
}

Organismo* IO::parseOrganismo(const QJsonValue& v) {
    if (!v.isObject()) throw new FileStructureError("Expected JSON Object while parsing Organismo");
    QJsonObject obj = v.toObject();

    QJsonValue type = obj.value("type");
    if (!type.isString()) throw new MissingProperty("type", "Organismo");
    std::string t = type.toString().toStdString();

    QJsonValue nameV = obj.value("name");
    if (!nameV.isString()) throw new MissingProperty("name", "Organismo");

    if (t == "TONNO") {
        return new Tonno(parseVect2D(obj.value("position")), nameV.toString().toStdString());
    }
    else if (t == "SARDINA") {
        return new Sardina(parseVect2D(obj.value("position")), nameV.toString().toStdString());
    }
    else if (t == "PHYTOPLANKTON") {
        return new Phytoplankton(parseVect2D(obj.value("position")), nameV.toString().toStdString());
    }
    else throw new FileStructureError("Unknown Type: " + t);
}
