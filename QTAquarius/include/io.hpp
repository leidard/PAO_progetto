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
class Phytoplankton;

class IO {
public:

    class FileStructureError : public std::exception {
        std::string msg;

    public:
        FileStructureError(const std::string& _msg = "General Parse Error");
        std::string getMsg() const;
    };

    class MissingProperty : public IO::FileStructureError {
    public:
        MissingProperty(std::string propertyname, std::string object = "");
    };

    static const std::string DEFAULT_FILENAME;

    void load(Aquarius* a, const std::string& filename = DEFAULT_FILENAME) const;
    void save(Aquarius* a, const std::string& filename = DEFAULT_FILENAME) const;

    static QJsonObject serialize(const Tonno&);
    static QJsonObject serialize(const Sardina&);
    static QJsonObject serialize(const Phytoplankton&);
    static QJsonObject serialize(const Vect2D&);

    static Vect2D parseVect2D(const QJsonValue&);
    static Organismo* parseOrganismo(const QJsonValue&);
};

#endif
