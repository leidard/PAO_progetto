#include <cmath>

#ifndef VECT_H
#define VECT_H

#include <../include/vect.h>

class Vect {
    friend Vect operator*(double, const Vect&);
    friend Vect operator/(double, const Vect&);

   private:
    double x, y;

   public:
    Vect();
    Vect(double coord_x, double coord_y);
    Vect(const Vect& v);

    // getters

    double getX() const;
    double getY() const;
    Vect getXVect() const;
    Vect getYVect() const;

    // non-const edit functions with chain return

    Vect& set(double, double);
    Vect& add(const Vect&);
    Vect& rem(const Vect&);
    Vect& mult(double);
    Vect& div(double);
    Vect& min(Vect&);
    Vect& max(Vect&);
    Vect& normalize();
    Vect& setMagnitude(double);
    Vect& limit(const Vect&);
    Vect& limit(double s);

    // const edit functions with chain return

    Vect set(double, double) const;
    Vect add(const Vect&) const;
    Vect rem(const Vect&) const;
    Vect mult(double) const;
    Vect div(double) const;
    Vect min(const Vect&) const;
    Vect max(const Vect&) const;
    Vect normalize() const;
    Vect setMagnitude(double) const;
    Vect limit(const Vect&) const;
    Vect limit(double s) const;
    double mag() const;
    double dot(const Vect& v) const;
    double distance(const Vect& v) const;
    double angleBetween(const Vect& v) const;
    Vect scalarProjection(const Vect& v) const;

    //static

    static Vect set(const Vect&, double, double);
    static Vect sum(const Vect&, const Vect&);
    static Vect rem(const Vect&, const Vect&);
    static Vect mult(const Vect&, double);
    static Vect div(const Vect&, double);
    static Vect min(const Vect&, const Vect&);
    static Vect max(const Vect&, const Vect&);
    static Vect normalize(const Vect&);
    static Vect setMagnitude(const Vect&, double);
    static Vect limit(const Vect&, const Vect&);
    static Vect limit(const Vect&, double);
    static double mag(const Vect&);
    static double dot(const Vect&, const Vect&);
    static double distance(const Vect&, const Vect&);
    static double angleBetween(const Vect&, const Vect&);
    static Vect scalarProjection(const Vect&, const Vect&);

    // operators

    Vect operator+(const Vect&) const;  // call sum
    Vect operator-(const Vect&) const;  // call sub
    Vect operator*(double) const;       // call mult
    Vect operator/(double) const;       // call div

    Vect& operator+=(const Vect&);  // call sum
    Vect& operator-=(const Vect&);  // call div
    Vect& operator*=(double);       // call mult
    Vect& operator/=(double);       // call div

    // comparison operators

    bool operator>(const Vect&) const;
    bool operator>=(const Vect&) const;
    bool operator<(const Vect&) const;
    bool operator<=(const Vect&) const;
    virtual bool operator==(const Vect&) const;
    virtual bool operator!=(const Vect&) const;  // controllo riferimento
};

#endif