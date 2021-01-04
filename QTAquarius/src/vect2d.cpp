#include "vect2d.hpp"

#include <algorithm>
#include <cmath>
#include <utility>

Vect2D::Vect2D() : _x(0), _y(0){};
Vect2D::Vect2D(double x, double y) : _x(x), _y(y) {}
Vect2D::Vect2D(const Vect2D& v) : _x(v._x), _y(v._y) {}

Vect2D& Vect2D::operator=(const Vect2D& v) {
    if (this != &v) {
        _x = v._x;
        _y = v._y;
    }
    return *this;
}

// getters

double Vect2D::x() const { return _x; }
double Vect2D::y() const { return _y; }
double& Vect2D::rx() { return _x; }
double& Vect2D::ry() { return _y; }
Vect2D Vect2D::getXVect() const { return Vect2D(_x, 0); }
Vect2D Vect2D::getYVect() const { return Vect2D(0, _y); }
std::pair<double, double> Vect2D::getPair() const { return std::pair<double, double>(_x, _y); }

// non-const edit functions with chain return

Vect2D& Vect2D::set(double x, double y) {
    _x = x;
    _y = y;
    return *this;
}
Vect2D& Vect2D::add(const Vect2D& v) {
    _x += v._x;
    _y += v._y;
    return *this;
}
Vect2D& Vect2D::rem(const Vect2D& v) {
    _x -= v._x;
    _y -= v._y;
    return *this;
}
Vect2D& Vect2D::mult(double s) {
    _x *= s;
    _y *= s;
    return *this;
}
Vect2D& Vect2D::div(double s) {
    _x /= s;
    _y /= s;
    return *this;
}
Vect2D& Vect2D::min(Vect2D& v) { return (*this < v) ? *this : v; }
Vect2D& Vect2D::max(Vect2D& v) { return (*this > v) ? *this : v; }
Vect2D& Vect2D::normalize() {
    double m = mag();
    return m == 0 ? set(0, 0) : div(m);
}
Vect2D& Vect2D::setMagnitude(double m) { return normalize().mult(m); }
Vect2D& Vect2D::limit(const Vect2D& v) {
    _x = std::min(_x, v._x);
    _y = std::min(_y, v._y);
    return *this;
}
Vect2D& Vect2D::limit(double s) {
    _x = std::min(_x, s);
    _y = std::min(_y, s);
    return *this;
}
Vect2D& Vect2D::bounds(const Vect2D& b) {
    if (_x > b._x)
        _x = 0;
    else if (_x < 0)
        _x = b._x;
    if (_y > b._y)
        _y = 0;
    else if (_y < 0)
        _y = b._y;
    return *this;
}
// this is rad
Vect2D& Vect2D::rotate(double rad) {  // anti-clockwise
    double x2 = _x * std::cos(rad) - _y * std::sin(rad);
    _y = _x * std::sin(rad) + _y * std::cos(rad);
    _x = x2;
    return *this;
}
Vect2D& Vect2D::rotateDeg(double deg) {  // anti-clockwise
    double rad = deg * M_PI / 180;
    double x2 = _x * std::cos(rad) - _y * std::sin(rad);
    _y = _x * std::sin(rad) + _y * std::cos(rad);
    _x = x2;
    return *this;
}

// const edit functions with chain return

Vect2D Vect2D::set(double x, double y) const { return Vect2D(*this).set(x, y); }
Vect2D Vect2D::add(const Vect2D& v) const { return Vect2D(*this).add(v); }
Vect2D Vect2D::rem(const Vect2D& v) const { return Vect2D(*this).rem(v); }
Vect2D Vect2D::mult(double s) const { return Vect2D(*this).mult(s); }
Vect2D Vect2D::div(double s) const { return Vect2D(*this).div(s); }
Vect2D Vect2D::min(Vect2D& v) const { return Vect2D(*this).min(v); }
Vect2D Vect2D::max(Vect2D& v) const { return Vect2D(*this).max(v); }
Vect2D Vect2D::normalize() const { return Vect2D(*this).normalize(); }
Vect2D Vect2D::setMagnitude(double s) const { return Vect2D(*this).setMagnitude(s); }
Vect2D Vect2D::limit(const Vect2D& v) const { return Vect2D(*this).limit(v); }
Vect2D Vect2D::limit(double s) const { return Vect2D(*this).limit(s); }
Vect2D Vect2D::bounds(const Vect2D& b) const { return Vect2D(*this).bounds(b); }
Vect2D Vect2D::rotate(double rad) const { return Vect2D(*this).rotate(rad); }
Vect2D Vect2D::rotateDeg(double deg) const { return Vect2D(*this).rotateDeg(deg); }
double Vect2D::mag() const { return std::sqrt(_x * _x + _y * _y); }
double Vect2D::dot(const Vect2D& v) const { return _x * v._x + _y * v._y; }
double Vect2D::distance(const Vect2D& v) const { return (*this - v).mag(); }
double Vect2D::angleRad() const { return std::atan2(_y, _x); }
double Vect2D::angleDeg() const { return std::atan2(_y, _x) * 180 / M_PI; }
double Vect2D::angleBetweenRad(const Vect2D& v) const { return std::acos(dot(v) / (mag() * v.mag())); }
double Vect2D::angleBetweenDeg(const Vect2D& v) const { return angleBetweenRad(v) * 180 / M_PI; }
Vect2D Vect2D::scalarProjection(const Vect2D& v) const { return v.normalize().mult(dot(v)); }

//static

Vect2D Vect2D::set(const Vect2D& v, double x, double y) { return v.set(x, y); }
Vect2D Vect2D::sum(const Vect2D& v1, const Vect2D& v2) { return v1.add(v2); }
Vect2D Vect2D::sub(const Vect2D& v1, const Vect2D& v2) { return v1.rem(v2); }
Vect2D Vect2D::mult(const Vect2D& v1, double s) { return v1.mult(s); }
Vect2D Vect2D::div(const Vect2D& v1, double s) { return v1.div(s); }
Vect2D Vect2D::min(Vect2D& v1, Vect2D& v2) { return v1.min(v2); }
Vect2D Vect2D::max(Vect2D& v1, Vect2D& v2) { return v1.max(v2); }
Vect2D Vect2D::normalize(const Vect2D& v1) { return v1.normalize(); }
Vect2D Vect2D::setMagnitude(const Vect2D& v1, double s) { return v1.setMagnitude(s); }
Vect2D Vect2D::limit(const Vect2D& v1, const Vect2D& v2) { return v1.limit(v2); }
Vect2D Vect2D::limit(const Vect2D& v1, double s) { return v1.limit(s); }
Vect2D Vect2D::rotate(const Vect2D& v1, double rad) { return v1.rotate(rad); }
Vect2D Vect2D::rotateDeg(const Vect2D& v1, double deg) { return v1.rotateDeg(deg); }
double Vect2D::mag(const Vect2D& v1) { return v1.mag(); }
double Vect2D::dot(const Vect2D& v1, const Vect2D& v2) { return v1.dot(v2); }
double Vect2D::distance(const Vect2D& v1, const Vect2D& v2) { return v1.distance(v2); }
double Vect2D::angleBetweenRad(const Vect2D& v1, const Vect2D& v2) { return v1.angleBetweenRad(v2); }
double Vect2D::angleBetweenDeg(const Vect2D& v1, const Vect2D& v2) { return v1.angleBetweenDeg(v2); }
Vect2D Vect2D::scalarProjection(const Vect2D& v1, const Vect2D& v2) { return v1.scalarProjection(v2); }

// operators

Vect2D Vect2D::operator+(const Vect2D& v) const { return this->add(v); }  // call sum
Vect2D Vect2D::operator-(const Vect2D& v) const { return this->rem(v); }  // call sub
Vect2D Vect2D::operator*(double s) const { return this->mult(s); }        // call mult
Vect2D Vect2D::operator/(double s) const { return this->div(s); }         // call div
Vect2D Vect2D::operator-() const { return Vect2D(*this).mult(-1); }

Vect2D& Vect2D::operator+=(const Vect2D& v) { return this->add(v); }  // call sum
Vect2D& Vect2D::operator-=(const Vect2D& v) { return this->rem(v); }  // call div
Vect2D& Vect2D::operator*=(double s) { return this->mult(s); }        // call mult
Vect2D& Vect2D::operator/=(double s) { return this->div(s); }         // call div

// comparison operators

bool Vect2D::operator>(const Vect2D& v2) const {
    return _x > v2._x && _y > v2._y;
}
bool Vect2D::operator>=(const Vect2D& v2) const {
    return _x >= v2._x && _y >= v2._y;
}
bool Vect2D::operator<(const Vect2D& v2) const {
    return _x < v2._x && _y < v2._y;
}
bool Vect2D::operator<=(const Vect2D& v2) const {
    return _x <= v2._x && _y <= v2._y;
}
bool Vect2D::operator==(const Vect2D& v2) const {
    return this == &v2 || (_x == v2._x && _y == v2._y);
}
bool Vect2D::operator!=(const Vect2D& v2) const {
    return this != &v2 && (_x != v2._x || _y != v2._y);  // applying de morgan laws to the negated operator==
}

// Vect2D::operator QPoint() { return QPoint(_x, _y); }

Vect2D::operator std::pair<double, double>() const { return std::pair<double, double>(_x, _y); };

// external operators (friends)

Vect2D operator*(double s, const Vect2D& v) { return v.mult(s); }

Vect2D operator/(double s, const Vect2D& v) { return v.div(s); }
