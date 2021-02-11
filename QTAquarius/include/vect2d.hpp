#include <iostream>
#ifndef VECT_H
#define VECT_H

/**
 * Two Dimensional Vector
*/
class Vect2D {
    friend Vect2D operator*(double, const Vect2D&);
    friend Vect2D operator/(double, const Vect2D&);
    friend std::ostream& operator<<(std::ostream& os, const Vect2D&);

private:
    double _x, _y;

public:
    static const Vect2D ZERO;

    Vect2D();
    Vect2D(double x, double y);

    // getters
    double x() const;
    double y() const;
    double& rx();
    double& ry();
    std::pair<double, double> getPair() const;

    // non-const edit functions with chain return by reference

    /**
     * Set the values of the vector
     * @param double x
     * @param double y
     * @return reference to *this
    */
    Vect2D& set(double, double);

    /**
     * Sum the Vect2D passed by parameter to this vector
     * @param Vect2D
     * @return reference to *this
    */
    Vect2D& add(const Vect2D&);

    /**
     * Subtract the Vect2D passed by parameter to this vector
     * @param Vect2D
     * @return reference to *this
    */
    Vect2D& rem(const Vect2D&);

    /**
     * Multiply by the scalar passed by parameter to this vector
     * @param double scalar
     * @return reference to *this
    */
    Vect2D& mult(double);

    /**
     * Divide by the scalar passed by parameter to this vector
     * @param double scalar
     * @return reference to *this
    */
    Vect2D& div(double);

    /**
     * Get the mininum between this vector and the one passed by parameter
     * @param Vect2D
     * @return reference to *this
    */
    Vect2D& min(Vect2D&);

    /**
     * Get the maximum between this vector and the one passed by parameter
     * @param Vect2D
     * @return reference to *this
    */
    Vect2D& max(Vect2D&);

    /**
     * Normalize this vector to the unit vector
     * @return reference to *this
    */
    Vect2D& normalize();

    /**
     * normalize and set the magnitude to the specified by parameter
     * @param double magnitude
     * @return reference to *this
    */
    Vect2D& setMagnitude(double);

    /**
     * if the magnitude is greater than the paramter, set the magnitude to the parameter
     * @param double max magnitude
     * @return reference to *this
    */
    Vect2D& limit(double);

    /**
     * Keep the vector x and y within some range
     * @param Vect2D
     * @return reference to *this
    */
    Vect2D& bounds(const Vect2D&);

    /**
     * Rotate the vector in Radians
     * @param double radians
     * @return reference to *this
    */
    Vect2D& rotateRad(double);

    /**
     * Rotate the vector in Degrees
     * @param double degrees
     * @return reference to *this
    */
    Vect2D& rotateDeg(double);
    Vect2D& reset();

    // const edit functions with chain return by value

    Vect2D set(double, double) const;
    Vect2D add(const Vect2D&) const;
    Vect2D rem(const Vect2D&) const;
    Vect2D mult(double) const;
    Vect2D div(double) const;
    Vect2D min(Vect2D&) const;
    Vect2D max(Vect2D&) const;
    Vect2D normalize() const;
    Vect2D setMagnitude(double) const;
    Vect2D limit(double) const;
    Vect2D bounds(const Vect2D&) const;
    Vect2D rotateRad(double) const;
    Vect2D rotateDeg(double) const;
    Vect2D reset() const;
    double mag() const;
    double dot(const Vect2D&) const;
    double distance(const Vect2D&) const;
    double angleRad() const;
    double angleDeg() const;
    double angleBetweenRad(const Vect2D&) const;
    double angleBetweenDeg(const Vect2D&) const;
    /**
     * Projects this vector on the vector passed as parameter
    */
    Vect2D scalarProjection(const Vect2D&) const;

    //static

    static Vect2D set(const Vect2D&, double, double);
    static Vect2D sum(const Vect2D&, const Vect2D&);
    static Vect2D sub(const Vect2D&, const Vect2D&);
    static Vect2D mult(const Vect2D&, double);
    static Vect2D div(const Vect2D&, double);
    static Vect2D min(Vect2D&, Vect2D&);
    static Vect2D max(Vect2D&, Vect2D&);
    static Vect2D normalize(const Vect2D&);
    static Vect2D setMagnitude(const Vect2D&, double);
    static Vect2D limit(const Vect2D&, double);
    static Vect2D rotateRad(const Vect2D&, double);
    static Vect2D rotateDeg(const Vect2D&, double);
    static Vect2D reset(const Vect2D&);
    static double mag(const Vect2D&);
    static double dot(const Vect2D&, const Vect2D&);
    static double distance(const Vect2D&, const Vect2D&);
    static double angleBetweenRad(const Vect2D&, const Vect2D&);
    static double angleBetweenDeg(const Vect2D&, const Vect2D&);
    static Vect2D scalarProjection(const Vect2D&, const Vect2D&);

    // operators

    Vect2D operator+(const Vect2D&) const;  // call sum
    Vect2D operator-(const Vect2D&) const;  // call sub
    Vect2D operator*(double) const;         // call mult
    Vect2D operator/(double) const;         // call div
    Vect2D operator-() const;

    Vect2D& operator+=(const Vect2D&);  // call sum
    Vect2D& operator-=(const Vect2D&);  // call div
    Vect2D& operator*=(double);         // call mult
    Vect2D& operator/=(double);         // call div

    // comparison operators

    bool operator>(const Vect2D&) const;
    bool operator>=(const Vect2D&) const;
    bool operator<(const Vect2D&) const;
    bool operator<=(const Vect2D&) const;
    bool operator==(const Vect2D&) const;
    bool operator!=(const Vect2D&) const;

    // converters
    operator std::pair<double, double>() const;
};

#endif
