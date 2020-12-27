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
#include "vect2d.hpp"
#include "vegetale.hpp"
#include "vitalita.hpp"

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

    if (!o.value("fishArr").isArray()) throw new ParseError("Can't find fishArr");
    if (!o.value("vegArr").isArray()) throw new ParseError("Can't find vegArr");
    // TODO WIDTH, HEIGHT

    Aquarius::init();
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

void SaverLoader::save(const Aquarius* a) const {
}

QJsonObject SaverLoader::serialize(const Vegetale& f) {
    QJsonObject o = QJsonObject();
    o.insert("position", serialize(f.getPosition()));
    o.insert("visibility", f.getVisibility());
    // o.insert("valoreNutrizionale", f.getValoreNutrizionale());
    return o;
}

QJsonObject SaverLoader::serialize(const Predatore& f) {
    QJsonObject o = QJsonObject();
    o.insert("type", "PREDATORE");
    o.insert("position", serialize(f.getPosition()));
    o.insert("velocity", serialize(f.getVelocity()));
    o.insert("daynight", serialize(f.getDayCycle()));
    o.insert("visibility", f.getVisibility());
    // o.insert("valoreNutrizionale", f.getValoreNutrizionale());
    return o;
}

QJsonObject SaverLoader::serialize(const Preda& f) {
    QJsonObject o = QJsonObject();
    o.insert("type", "PREDA");
    o.insert("position", serialize(f.getPosition()));
    o.insert("velocity", serialize(f.getVelocity()));
    o.insert("daynight", serialize(f.getDayCycle()));
    o.insert("visibility", f.getVisibility());
    // o.insert("valoreNutrizionale", f.getValoreNutrizionale());
    return o;
}

QJsonObject SaverLoader::serialize(const DayCycle& d) {
    QJsonObject o = QJsonObject();
    o.insert("awakeTime", d.getDayTime());
    o.insert("asleepTime", d.getNightTime());
    o.insert("progress", d.getProgress());
    return o;
}

QJsonObject SaverLoader::serialize(const Stamina& s) {
    QJsonObject o = QJsonObject();
    o.insert("val", s.getVal());
    o.insert("max", (int)s.getMax());
    return o;
}

QJsonObject SaverLoader::serialize(const Vect2D& v) {
    QJsonObject o = QJsonObject();
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

DayCycle SaverLoader::parseDayCycle(const QJsonValue& v) {
    if (!v.isObject()) throw new ParseError("parseDayCycle: not a JSON Object");
    QJsonObject o = v.toObject();

    QJsonValue awakeTime = o.value("awakeTime");
    if (awakeTime.isDouble()) throw new ParseError("parseStamina: can't read property \"awakeTime\"");
    QJsonValue asleepTime = o.value("asleepTime");
    if (asleepTime.isDouble()) throw new ParseError("parseStamina: can't read property \"asleepTime\"");
    QJsonValue progress = o.value("progress");
    if (progress.isDouble()) throw new ParseError("parseStamina: can't read property \"progress\"");

    return DayCycle(awakeTime.toDouble(), asleepTime.toDouble(), progress.toDouble());
}

Stamina SaverLoader::parseStamina(const QJsonValue& v) {
    if (!v.isObject()) throw new ParseError("parseStamina: not a JSON Object");
    QJsonObject o = v.toObject();

    QJsonValue val = o.value("val");
    if (val.isDouble()) throw new ParseError("parseStamina: can't read property \"val\"");
    QJsonValue max = o.value("max");
    if (max.isDouble()) throw new ParseError("parseStamina: can't read property \"max\"");

    return Stamina(val.toDouble(), max.toDouble());
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
        QJsonValue awake = o.value("awake");
        if (!awake.isBool()) throw new ParseError("parsePredatore: can't read property \"name\"");

        return new Predatore(parseVect2D(o.value("position")), parseVect2D(o.value("velocity")), name.toString().toStdString(), awake.toBool(), parseDayCycle(o.value("daynight")), parseStamina(o.value("stamina")));
    } else if (t == "PREDA") {
        QJsonValue name = o.value("name");
        if (!name.isString()) throw new ParseError("parsePredatore: can't read property \"name\"");
        QJsonValue awake = o.value("awake");
        if (!awake.isBool()) throw new ParseError("parsePredatore: can't read property \"name\"");

        return new Preda(parseVect2D(o.value("position")), parseVect2D(o.value("velocity")), name.toString().toStdString(), awake.toBool(), parseDayCycle(o.value("daynight")), parseStamina(o.value("stamina")));
    } else
        throw new ParseError("parsePredatore: ");
}
