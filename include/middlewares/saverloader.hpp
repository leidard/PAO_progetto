#include <exception>
#include <iostream>
#include <string>

#include "vector.hpp"
#ifndef JSONPARSER_H
#define JSONPARSER_H

class Aquarius;

class Food;
class Fish;
class DayCycle;
class Stamina;
class Vect2D;
class Predatore;
class Preda;
class Vegetale;

class SaverLoader {
   public:
    class ParseError : public std::exception {
        const char* msg;

       public:
        ParseError(std::string _msg = "General Parse Error");
        const char* what() const throw();
    };

    static const std::string DEFAULT_FILENAME;
    void load(const std::string& file = DEFAULT_FILENAME) const;
    void save(const Aquarius*) const;

    static QJsonObject serialize(const Vegetale&);
    static QJsonObject serialize(const Predatore&);
    static QJsonObject serialize(const Preda&);
    static QJsonObject serialize(const DayCycle&);
    static QJsonObject serialize(const Stamina&);
    static QJsonObject serialize(const Vect2D&);

    static Vegetale* parseVegetale(const QJsonValue&);
    static DayCycle parseDayCycle(const QJsonValue&);
    static Stamina parseStamina(const QJsonValue&);
    static Vect2D parseVect2D(const QJsonValue&);
    static Fish* parseFish(const QJsonValue&);
};

#endif