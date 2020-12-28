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
#include "food.hpp"
#include "preda.hpp"
#include "predatore.hpp"
#include "stamina.hpp"
#include "vect2d.hpp"
#include "vegetale.hpp"

SaverLoader::ParseError::ParseError(std::string _msg) : msg(std::string("[JSON ParseError]: " + _msg).c_str()) {}

const char* SaverLoader::ParseError::what() const throw() { return msg; }

const std::string SaverLoader::DEFAULT_FILENAME = "aquarius.save.json";

void SaverLoader::load(const std::string& filename) const {
    QFile file;
    file.setFileName(filename.c_str());
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString val = file.readAll();
    file.close();
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    if (!d.isObject()) throw new ParseError("Root must be an Object");
    QJsonObject o = d.object();

    if (!o.value("fishArr").isArray()) throw new ParseError("Can't find property: fishArr");
    if (!o.value("vegArr").isArray()) throw new ParseError("Can't find property: vegArr");
    if (!o.value("width").isDouble()) throw new ParseError("Can't find property: width");
    if (!o.value("height").isDouble()) throw new ParseError("Can't find property: height");

    Aquarius::init(o.value("width").toDouble(), o.value("height").toDouble());
    Aquarius* aq = Aquarius::getInstance();

    for (auto i : o.value("fishArr").toArray()) {
        try {
            aq->addFish(parseFish(i));
        } catch (ParseError& err) {
            std::cerr << err.what();  // show but keep going
        }
    }

    for (auto i : o.value("fishArr").toArray()) {
        try {
            aq->addFood(parseVegetale(i));
        } catch (ParseError& err) {
            std::cerr << err.what();  // show but keep going
        }
    }
}

void SaverLoader::save(const std::string& filename) const {
    auto asda = filename;
    Aquarius* a = Aquarius::getInstance();

    QJsonObject o;
    o.insert("width", (int)a->getWidth());
    o.insert("height", (int)a->getHeight());
    QJsonArray fishArr;

    for (auto f : a->getAllFish()) {
        Predatore* predatore = dynamic_cast<Predatore*>(&*f);
        if (predatore != nullptr) {
            // fishArr.push_back(SaverLoader::serialize(*predatore));
            continue;
        }
        //Preda* preda = dynamic_cast<Preda*>(&*f);
        //if (preda != nullptr) {
            // fishArr.push_back(SaverLoader::serialize(*preda));
           // continue;
        //}
    }

    QJsonArray vegArr;

    for (auto f : a->getAllFood()) {
        Vegetale* vegetale = dynamic_cast<Vegetale*>(&*f);
        if (vegetale != nullptr) {
            //vegArr.push_back(SaverLoader::serialize(*vegetale));
        }
    }

    o.insert("fishArr", fishArr);
    o.insert("vegArr", vegArr);
    // o.insert("valoreNutrizionale", f.getValoreNutrizionale());
}

QJsonObject SaverLoader::serialize(const Vegetale& f) {
    QJsonObject o = QJsonObject();
    o.insert("position", SaverLoader::serialize(f.getPosition()));
    o.insert("visibility", f.getVisibility());
    // o.insert("valoreNutrizionale", f.getValoreNutrizionale());
    return o;
}

QJsonObject SaverLoader::serialize(const Predatore& f) {
    QJsonObject o;
    o.insert("type", "PREDATORE");
    o.insert("position", SaverLoader::serialize(f.getPosition()));
    o.insert("velocity", SaverLoader::serialize(f.getVelocity()));
    o.insert("visibility", f.getVisibility());
    // o.insert("valoreNutrizionale", f.getValoreNutrizionale());
    return o;
}

QJsonObject SaverLoader::serialize(const Preda& f) {
    QJsonObject o;
    o.insert("type", "PREDA");
    o.insert("position", SaverLoader::serialize(f.getPosition()));
    o.insert("velocity", SaverLoader::serialize(f.getVelocity()));
    o.insert("visibility", f.getVisibility());
    // o.insert("valoreNutrizionale", f.getValoreNutrizionale());
    return o;
}

QJsonObject SaverLoader::serialize(const Vect2D& v) {
    QJsonObject o;
    o.insert("x", v.x());
    o.insert("y", v.y());
    return o;
}

Vegetale* SaverLoader::parseVegetale(const QJsonValue& v) {
    if (!v.isObject()) throw new ParseError("parseVegetale: not a JSON Object");
    QJsonObject o = v.toObject();

    QJsonValue visibility = o.value("visibility");
    if (!visibility.isDouble()) throw new ParseError("parseVegetale: can't read property \"visibility\"");

    return new Vegetale(parseVect2D(o.value("position").toString()), visibility.toDouble());
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
        QJsonValue imagepath = o.value("imagepath");
        if (!imagepath.isString()) throw new ParseError("parsePredatore: can't read property \"name\"");

        return new Predatore(parseVect2D(o.value("position")), name.toString().toStdString());
    } else if (t == "PREDA") {
        QJsonValue name = o.value("name");
        if (!name.isString()) throw new ParseError("parsePredatore: can't read property \"name\"");

        //return new Preda(parseVect2D(o.value("position")), name.toString().toStdString());
        return nullptr;
    } else
        throw new ParseError("parsePredatore: ");
}
