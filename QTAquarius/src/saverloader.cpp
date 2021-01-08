#include "saverloader.hpp"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QtGlobal>
#include <string>

#include "aquarius.hpp"
#include "preda.hpp"
#include "predatore.hpp"

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
    QJsonObject o = d.object();

    if (!o.value("fish").isArray()) throw new ParseError("Can't find property: fish");
    if (!o.value("width").isDouble()) throw new ParseError("Can't find property: width");
    if (!o.value("height").isDouble()) throw new ParseError("Can't find property: height");

    a->setSize(o.value("width").toDouble(), o.value("height").toDouble());

    auto arr = o.value("fish").toArray();
    for (auto it = arr.begin(); it < arr.end(); it++) {
        auto i = *it;
        try {
            a->addFish(parseFish(i));
        } catch (ParseError& err) {
            std::cerr << err.what();  // show but keep going
        }
    }
}

void SaverLoader::save(Aquarius* a, const std::string& filename) const {
    auto asda = filename;

    QJsonObject o;
    o.insert("width", (int)a->getWidth());
    o.insert("height", (int)a->getHeight());
    QJsonArray fish;

    for (auto& f : a->getAllFish()) {
        if (Predatore* predatore = dynamic_cast<Predatore*>(&*f)) {
            fish.push_back(SaverLoader::serialize(*predatore));
        } else if (Preda* preda = dynamic_cast<Preda*>(&*f)) {
            fish.push_back(SaverLoader::serialize(*preda));
        }
    }

    o.insert("fish", fish);
}

QJsonObject SaverLoader::serialize(const Predatore& f) {
    QJsonObject o;
    o.insert("type", "PREDATORE");
    o.insert("position", SaverLoader::serialize(f.getPosition()));
    o.insert("name", f.getName().c_str());

    return o;
}

QJsonObject SaverLoader::serialize(const Preda& f) {
    QJsonObject o;
    o.insert("type", "PREDA");
    o.insert("position", SaverLoader::serialize(f.getPosition()));
    o.insert("name", f.getName().c_str());

    return o;
}

QJsonObject SaverLoader::serialize(const Vect2D& v) {
    QJsonObject o;
    o.insert("x", v.x());
    o.insert("y", v.y());
    return o;
}

Vect2D SaverLoader::parseVect2D(const QJsonValue& v) {
    if (!v.isObject()) throw new ParseError("parseVect2D: not a JSON Object");
    QJsonObject o = v.toObject();

    QJsonValue x = o.value("x");
    if (!x.isDouble()) throw new ParseError("parseVect2D: can't read property \"x\"");
    QJsonValue y = o.value("y");
    if (!y.isDouble()) throw new ParseError("parseVect2D: can't read property \"y\"");

    return Vect2D(x.toDouble(), y.toDouble());
}

Fish* SaverLoader::parseFish(const QJsonValue& v) {
    if (!v.isObject()) throw new ParseError("parsePredatore: not a JSON Object");
    QJsonObject o = v.toObject();

    QJsonValue type = o.value("type");
    if (type.isString()) throw new ParseError("parsePredatore: missing type");
    QString t = type.toString();
    if (t == "PREDATORE") {
        QJsonValue name = o.value("name");
        if (!name.isString()) throw new ParseError("parsePredatore: can't read property \"name\"");

        return new Predatore(parseVect2D(o.value("position")), name.toString().toStdString());
    } else if (t == "PREDA") {
        QJsonValue name = o.value("name");
        if (!name.isString()) throw new ParseError("parsePredatore: can't read property \"name\"");

        return new Preda(parseVect2D(o.value("position")), name.toString().toStdString());
        return nullptr;
    } else
        throw new ParseError("parsePredatore: ");
}
