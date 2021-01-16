#include <QJsonObject>
#include <QJsonValue>
#include <exception>
#include <iostream>
#include <string>

#ifndef SAVERLOADER_H
#define SAVERLOADER_H

class Aquarius;

class Vect2D;
class Tonno;
class Sardina;
class Organismo;

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

    static QJsonObject serialize(const Tonno&);
    static QJsonObject serialize(const Sardina&);
    static QJsonObject serialize(const Vect2D&);

    static Vect2D parseVect2D(const QJsonValue&);
    static Organismo* parseOrganismo(const QJsonValue&);
};

#endif
