#include <algorithm>

#include "vect2d.h"

Vect2D::Vect2D() : x(0), y(0){};
Vect2D::Vect2D(double coord_x, double coord_y) : x(coord_x), y(coord_y) {}
Vect2D::Vect2D(const Vect2D& v) : x(v.x), y(v.y) {}

// getters

double Vect2D::getX() const { return x; }
double Vect2D::getY() const { return y; }
Vect2D Vect2D::getXVect() const { return Vect2D(x, 0); }
Vect2D Vect2D::getYVect() const { return Vect2D(0, y); }

// non-const edit functions with chain return

Vect2D& Vect2D::set(double coord_x, double coord_y) {
    x = coord_x;
    y = coord_y;
    return *this;
}
Vect2D& Vect2D::add(const Vect2D& v) {
    x += v.x;
    y += v.y;
    return *this;
}
Vect2D& Vect2D::rem(const Vect2D& v) {
    x -= v.x;
    y -= v.y;
    return *this;
}
Vect2D& Vect2D::mult(double s) {
    x *= s;
    y *= s;
    return *this;
}
Vect2D& Vect2D::div(double s) {
    x /= s;
    y /= s;
    return *this;
}
Vect2D& Vect2D::min(Vect2D& v) { return (*this < v) ? *this : v; }
Vect2D& Vect2D::max(Vect2D& v) { return (*this > v) ? *this : v; }
Vect2D& Vect2D::normalize() { return this->div(mag()); }
Vect2D& Vect2D::setMagnitude(double m) { return this->normalize().mult(m); }
Vect2D& Vect2D::limit(const Vect2D& v) {
    x = std::min(x, v.x);
    y = std::min(y, v.y);
    return *this;
}
Vect2D& Vect2D::limit(double s) {
    x = std::min(x, s);
    y = std::min(y, s);
    return *this;
}

// const edit functions with chain return

Vect2D Vect2D::set(double x, double y) const { return Vect2D(*this).set(x, y); }
Vect2D Vect2D::add(const Vect2D& v) const { return Vect2D(*this).add(v); }
Vect2D Vect2D::rem(const Vect2D& v) const { return Vect2D(*this).rem(v); }
Vect2D Vect2D::mult(double s) const { return Vect2D(*this).mult(s); }
Vect2D Vect2D::div(double s) const { return Vect2D(*this).div(s); }
Vect2D Vect2D::min(const Vect2D& v) const { return Vect2D(*this).min(v); }
Vect2D Vect2D::max(const Vect2D& v) const { return Vect2D(*this).max(v); }
Vect2D Vect2D::normalize() const { return Vect2D(*this).normalize(); }
Vect2D Vect2D::setMagnitude(double s) const { return Vect2D(*this).setMagnitude(s); }
Vect2D Vect2D::limit(const Vect2D& v) const { return Vect2D(*this).limit(v); }
Vect2D Vect2D::limit(double s) const { return Vect2D(*this).limit(s); }
double Vect2D::mag() const { return std::sqrt(x * x + y * y); }
double Vect2D::dot(const Vect2D& v) const { return x * v.x + y * v.y; }
double Vect2D::distance(const Vect2D& v) const { return this->rem(v).mag(); }
double Vect2D::angleBetween(const Vect2D& v) const { return std::acos(this->dot(v) / (this->mag() * v.mag())); }
Vect2D Vect2D::scalarProjection(const Vect2D& v) const { return v.normalize().mult(this->dot(v)); }

//static

Vect2D Vect2D::set(const Vect2D& v, double x, double y) { return v.set(x, y); }
Vect2D Vect2D::sum(const Vect2D& v1, const Vect2D& v2) { return v1.add(v2); }
Vect2D Vect2D::rem(const Vect2D& v1, const Vect2D& v2) { return v1.rem(v2); }
Vect2D Vect2D::mult(const Vect2D& v1, double s) { return v1.mult(s); }
Vect2D Vect2D::div(const Vect2D& v1, double s) { return v1.div(s); }
Vect2D Vect2D::min(const Vect2D& v1, const Vect2D& v2) { return v1.min(v2); }
Vect2D Vect2D::max(const Vect2D& v1, const Vect2D& v2) { return v1.max(v2); }
Vect2D Vect2D::normalize(const Vect2D& v1) { return v1.normalize(); }
Vect2D Vect2D::setMagnitude(const Vect2D& v1, double s) { return v1.setMagnitude(s); }
Vect2D Vect2D::limit(const Vect2D& v1, const Vect2D& v2) { return v1.limit(v2); }
Vect2D Vect2D::limit(const Vect2D& v1, double s) { return v1.limit(s); }
double Vect2D::mag(const Vect2D& v1) { return v1.mag(); }
double Vect2D::dot(const Vect2D& v1, const Vect2D& v2) { return v1.dot(v2); }
double Vect2D::distance(const Vect2D& v1, const Vect2D& v2) { return v1.distance(v2); }
double Vect2D::angleBetween(const Vect2D& v1, const Vect2D& v2) { return v1.angleBetween(v2); }
Vect2D Vect2D::scalarProjection(const Vect2D& v1, const Vect2D& v2) { return v1.scalarProjection(v2); }

// operators

Vect2D Vect2D::operator+(const Vect2D& v) const { return this->add(v); }  // call sum
Vect2D Vect2D::operator-(const Vect2D& v) const { return this->rem(v); }  // call sub
Vect2D Vect2D::operator*(double s) const { return this->mult(s); }        // call mult
Vect2D Vect2D::operator/(double s) const { return this->div(s); }         // call div

Vect2D& Vect2D::operator+=(const Vect2D& v) { return this->add(v); }  // call sum
Vect2D& Vect2D::operator-=(const Vect2D& v) { return this->rem(v); }  // call div
Vect2D& Vect2D::operator*=(double s) { return this->mult(s); }        // call mult
Vect2D& Vect2D::operator/=(double s) { return this->div(s); }         // call div

// comparison operators

bool Vect2D::operator>(const Vect2D& v2) const {
    return x > v2.x && y > v2.y;
}
bool Vect2D::operator>=(const Vect2D& v2) const {
    return x >= v2.x && y >= v2.y;
}
bool Vect2D::operator<(const Vect2D& v2) const {
    return x < v2.x && y < v2.y;
}
bool Vect2D::operator<=(const Vect2D& v2) const {
    return x <= v2.x && y <= v2.y;
}
bool Vect2D::operator==(const Vect2D& v2) const {
    return this == &v2 || (x == v2.x && y == v2.y);
}
bool Vect2D::operator!=(const Vect2D& v2) const {
    return this != &v2 && (x != v2.x || y != v2.y);  // applying de morgan laws to the negated operator==
}

// external operators (friends)

Vect2D operator*(double s, const Vect2D& v) { return v.mult(s); }

Vect2D operator/(double s, const Vect2D& v) { return v.div(s); }