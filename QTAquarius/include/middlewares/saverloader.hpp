#include <QJsonObject>
#include <QJsonValue>
#include <exception>
#include <iostream>
#include <string>

#include "vector.hpp"
#ifndef JSONPARSER_H
#define JSONPARSER_H

class Aquarius;

class Vect2D;
class Predatore;
class Preda;
class Fish;

class SaverLoader {
   public:
    class ParseError : public std::exception {
        const char* msg;

       public:
        ParseError(std::string _msg = "General Parse Error");
        ~ParseError() { delete msg; }
        const char* what() const throw();
    };

    static const std::string DEFAULT_FILENAME;

    void load(Aquarius* a, const std::string& filename = DEFAULT_FILENAME) const;
    void save(Aquarius* a, const std::string& filename = DEFAULT_FILENAME) const;

    static QJsonObject serialize(const Predatore&);
    static QJsonObject serialize(const Preda&);
    static QJsonObject serialize(const Vect2D&);

    static Vect2D parseVect2D(const QJsonValue&);
    static Fish* parseFish(const QJsonValue&);
};

#endif
