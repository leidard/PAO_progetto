#include "saverloader.hpp"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QtGlobal>
#include <string>

#include "aquarius.hpp"
#include "sardina.hpp"
#include "tonno.hpp"

SaverLoader::ParseError::ParseError(std::string _msg) : msg(std::string("[JSON ParseError]: " + _msg).c_str()) {}

const char* SaverLoader::ParseError::what() const throw() { return msg; }

const std::string SaverLoader::DEFAULT_FILENAME = "aquarius.json";

void SaverLoader::load(Aquarius* a, const std::string& filename) const {
    QFile file;
    file.setFileName(filename.c_str());
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString val = file.readAll();
    file.close();
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    if (!d.isObject()) throw new ParseError("Root must be an Object");
    QJsonObject obj = d.object();

    if (!obj.value("organismi").isArray()) throw new ParseError("Can't find property: organismi");
    if (!obj.value("width").isDouble()) throw new ParseError("Can't find property: width");
    if (!obj.value("height").isDouble()) throw new ParseError("Can't find property: height");

    a->setSize(obj.value("width").toDouble(), obj.value("height").toDouble());

    auto arr = obj.value("organismi").toArray();
    for (auto it = arr.begin(); it < arr.end(); it++) {
        auto i = *it;
        try {
            a->addOrganismo(parseOrganismo(i));
        } catch (ParseError& err) {
            std::cerr << err.what();  // show but keep going
        }
    }
}

void SaverLoader::save(Aquarius* a, const std::string& filename) const {
    auto asda = filename;

    QJsonObject obj;
    obj.insert("width", (int)a->getWidth());
    obj.insert("height", (int)a->getHeight());
    QJsonArray organismi;

    for (auto& o : a->getAllOrganismi()) {
        if (Tonno* tonno = dynamic_cast<Tonno*>(&*o)) {
            organismi.push_back(SaverLoader::serialize(*tonno));
        } else if (Sardina* sardina = dynamic_cast<Sardina*>(&*o)) {
            organismi.push_back(SaverLoader::serialize(*sardina));
        }
    }

    obj.insert("organismi", organismi);
}

QJsonObject SaverLoader::serialize(const Tonno& t) {
    QJsonObject obj;
    obj.insert("type", "TONNO");
    obj.insert("position", SaverLoader::serialize(t.getPosition()));
    obj.insert("name", t.getName().c_str());

    return obj;
}

QJsonObject SaverLoader::serialize(const Sardina& s) {
    QJsonObject obj;
    obj.insert("type", "SARDINA");
    obj.insert("position", SaverLoader::serialize(s.getPosition()));
    obj.insert("name", s.getName().c_str());

    return obj;
}

QJsonObject SaverLoader::serialize(const Vect2D& v) {
    QJsonObject obj;
    obj.insert("x", v.x());
    obj.insert("y", v.y());
    return obj;
}

Vect2D SaverLoader::parseVect2D(const QJsonValue& v) {
    if (!v.isObject()) throw new ParseError("parseVect2D: not a JSON Object");
    QJsonObject obj = v.toObject();

    QJsonValue x = obj.value("x");
    if (!x.isDouble()) throw new ParseError("parseVect2D: can't read property \"x\"");
    QJsonValue y = obj.value("y");
    if (!y.isDouble()) throw new ParseError("parseVect2D: can't read property \"y\"");

    return Vect2D(x.toDouble(), y.toDouble());
}

Organismo* SaverLoader::parseOrganismo(const QJsonValue& v) {
    if (!v.isObject()) throw new ParseError("parseTonno: not a JSON Object");
    QJsonObject obj = v.toObject();

    QJsonValue type = obj.value("type");
    if (type.isString()) throw new ParseError("parseTonno: missing type");
    QString t = type.toString();
    if (t == "TONNO") {
        QJsonValue name = obj.value("name");
        if (!name.isString()) throw new ParseError("parseTonno: can't read property \"name\"");

        return new Tonno(parseVect2D(obj.value("position")), name.toString().toStdString());
    } else if (t == "SARDINA") {
        QJsonValue name = obj.value("name");
        if (!name.isString()) throw new ParseError("parseSardina: can't read property \"name\"");

        return new Sardina(parseVect2D(obj.value("position")), name.toString().toStdString());
        return nullptr;
    } else
        throw new ParseError("parseSardina: ");
}
