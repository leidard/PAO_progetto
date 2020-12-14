#include <cmath>

#ifndef VECT_H
#define VECT_H

#include <../include/vect.h>

class Vect {
   private:
    double x, y;

   public:
    Vect();
    Vect(double coord_x, double coord_y);
    Vect(const Vect& v);
    double getX() const;
    double getY() const;
    Vect getXVect() const;
    Vect getYVect() const;

    // non-const edit functions with chain return

    Vect& add(const Vect&);
    Vect& sub(const Vect&);
    Vect& mult(double);
    Vect& div(double);
    Vect& min(const Vect&);
    Vect& max(const Vect&);
    Vect& normalize();
    Vect& setMagnitude(double);
    Vect& limit(const Vect&);
    Vect& limit(double s);

    // const edit functions with chain return

    Vect add(const Vect&) const;
    Vect sub(const Vect&) const;
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

    static Vect sum(const Vect&, const Vect&);
    static Vect sub(const Vect&, const Vect&);
    static Vect mult(const Vect&, double);
    static Vect div(const Vect&, double);
    static Vect min(const Vect&, const Vect&);
    static Vect max(const Vect&, const Vect&);
    static Vect normalize(const Vect&);
    static Vect setMagnitude(const Vect&, double);
    static Vect limit(const Vect&, const Vect&);
    static Vect limit(const Vect&, double s);
    static double mag(const Vect&);
    static double dot(const Vect&, const Vect&);
    static double distance(const Vect&, const Vect&);
    static double angleBetween(const Vect&, const Vect&);
    static Vect scalarProjection(const Vect&, const Vect&);

    Vect min(const Vect& v) const;
    Vect max(const Vect& v) const;

    Vect operator+(const Vect& v) const { return this->sum(v); };  // call sum
    Vect operator-(const Vect& v) const;                           // call sub
    Vect operator*(double n) const;                                // call mult
    Vect operator/(double n) const;                                // call div

    Vect& operator+=(const Vect& v);  // call sum
    Vect& operator-=(const Vect& v);  // call sum
    Vect& operator*=(double n);       // call sum
    Vect& operator/=(double n);

    bool operator>(const Vect& v2) const;
    bool operator>=(const Vect& v2) const;
    bool operator<(const Vect& v2) const;
    bool operator<=(const Vect& v2) const;
    virtual bool operator==(const Vect& v2) const;
    virtual bool operator!=(const Vect& v2) const;  // controllo riferimento
};

#endif