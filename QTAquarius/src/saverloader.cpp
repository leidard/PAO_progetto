#include "middlewares/saverloader.hpp"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <iostream>
#include <string>

#include "aquarius.hpp"
#include "daycycle.hpp"
#include "fish.hpp"
#include "preda.hpp"
#include "predatore.hpp"
#include "stamina.hpp"
#include "vect2d.hpp"

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

    for (auto i : o.value("fish").toArray()) {
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

    for (auto f : a->getAllFish()) {
        Predatore* predatore = dynamic_cast<Predatore*>(&*f);
        if (predatore != nullptr) {
            fish.push_back(SaverLoader::serialize(*predatore));
            continue;
        }
        Preda* preda = dynamic_cast<Preda*>(&*f);
        if (preda != nullptr) {
            fish.push_back(SaverLoader::serialize(*preda));
            continue;
        }
    }

    o.insert("fish", fish);
    // o.insert("valoreNutrizionale", f.getValoreNutrizionale());
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
