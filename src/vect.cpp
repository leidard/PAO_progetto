#include <../include/vect.h>

#include <algorithm>

Vect::Vect() : x(0), y(0){};
Vect::Vect(double coord_x, double coord_y) : x(coord_x), y(coord_y) {}
Vect::Vect(const Vect& v) : x(v.x), y(v.y) {}

// getters

double Vect::getX() const { return x; }
double Vect::getY() const { return y; }
Vect Vect::getXVect() const { return Vect(x, 0); }
Vect Vect::getYVect() const { return Vect(0, y); }

// non-const edit functions with chain return

Vect& Vect::set(double coord_x, double coord_y) {
    x = coord_x;
    y = coord_y;
    return *this;
}
Vect& Vect::add(const Vect& v) {
    x += v.x;
    y += v.y;
    return *this;
}
Vect& Vect::rem(const Vect& v) {
    x -= v.x;
    y -= v.y;
    return *this;
}
Vect& Vect::mult(double s) {
    x *= s;
    y *= s;
    return *this;
}
Vect& Vect::div(double s) {
    x /= s;
    y /= s;
    return *this;
}
Vect& Vect::min(Vect& v) { return (*this < v) ? *this : v; }
Vect& Vect::max(Vect& v) { return (*this > v) ? *this : v; }
Vect& Vect::normalize() { return this->div(mag()); }
Vect& Vect::setMagnitude(double m) { return this->normalize().mult(m); }
Vect& Vect::limit(const Vect& v) {
    x = std::min(x, v.x);
    y = std::min(y, v.y);
    return *this;
}
Vect& Vect::limit(double s) {
    x = std::min(x, s);
    y = std::min(y, s);
    return *this;
}

// const edit functions with chain return

Vect Vect::set(double x, double y) const { return Vect(*this).set(x, y); }
Vect Vect::add(const Vect& v) const { return Vect(*this).add(v); }
Vect Vect::rem(const Vect& v) const { return Vect(*this).rem(v); }
Vect Vect::mult(double s) const { return Vect(*this).mult(s); }
Vect Vect::div(double s) const { return Vect(*this).div(s); }
Vect Vect::min(const Vect& v) const { return Vect(*this).min(v); }
Vect Vect::max(const Vect& v) const { return Vect(*this).max(v); }
Vect Vect::normalize() const { return Vect(*this).normalize(); }
Vect Vect::setMagnitude(double s) const { return Vect(*this).setMagnitude(s); }
Vect Vect::limit(const Vect& v) const { return Vect(*this).limit(v); }
Vect Vect::limit(double s) const { return Vect(*this).limit(s); }
double Vect::mag() const { return std::sqrt(x * x + y * y); }
double Vect::dot(const Vect& v) const { return x * v.x + y * v.y; }
double Vect::distance(const Vect& v) const { return this->rem(v).mag(); }
double Vect::angleBetween(const Vect& v) const { return std::acos(this->dot(v) / (this->mag() * v.mag())); }
Vect Vect::scalarProjection(const Vect& v) const { return v.normalize().mult(this->dot(v)); }

//static

Vect Vect::set(const Vect& v, double x, double y) { return v.set(x, y); }
Vect Vect::sum(const Vect& v1, const Vect& v2) { return v1.add(v2); }
Vect Vect::rem(const Vect& v1, const Vect& v2) { return v1.rem(v2); }
Vect Vect::mult(const Vect& v1, double s) { return v1.mult(s); }
Vect Vect::div(const Vect& v1, double s) { return v1.div(s); }
Vect Vect::min(const Vect& v1, const Vect& v2) { return v1.min(v2); }
Vect Vect::max(const Vect& v1, const Vect& v2) { return v1.max(v2); }
Vect Vect::normalize(const Vect& v1) { return v1.normalize(); }
Vect Vect::setMagnitude(const Vect& v1, double s) { return v1.setMagnitude(s); }
Vect Vect::limit(const Vect& v1, const Vect& v2) { return v1.limit(v2); }
Vect Vect::limit(const Vect& v1, double s) { return v1.limit(s); }
double Vect::mag(const Vect& v1) { return v1.mag(); }
double Vect::dot(const Vect& v1, const Vect& v2) { return v1.dot(v2); }
double Vect::distance(const Vect& v1, const Vect& v2) { return v1.distance(v2); }
double Vect::angleBetween(const Vect& v1, const Vect& v2) { return v1.angleBetween(v2); }
Vect Vect::scalarProjection(const Vect& v1, const Vect& v2) { return v1.scalarProjection(v2); }

// operators

Vect Vect::operator+(const Vect& v) const { return this->add(v); }  // call sum
Vect Vect::operator-(const Vect& v) const { return this->rem(v); }  // call sub
Vect Vect::operator*(double s) const { return this->mult(s); }      // call mult
Vect Vect::operator/(double s) const { return this->div(s); }       // call div

Vect& Vect::operator+=(const Vect& v) { return this->add(v); }  // call sum
Vect& Vect::operator-=(const Vect& v) { return this->rem(v); }  // call div
Vect& Vect::operator*=(double s) { return this->mult(s); }      // call mult
Vect& Vect::operator/=(double s) { return this->div(s); }       // call div

// comparison operators

bool Vect::operator>(const Vect& v2) const {
    return x > v2.x && y > v2.y;
}
bool Vect::operator>=(const Vect& v2) const {
    return x >= v2.x && y >= v2.y;
}
bool Vect::operator<(const Vect& v2) const {
    return x < v2.x && y < v2.y;
}
bool Vect::operator<=(const Vect& v2) const {
    return x <= v2.x && y <= v2.y;
}
bool Vect::operator==(const Vect& v2) const {
    return this == &v2 || (x == v2.x && y == v2.y);
}
bool Vect::operator!=(const Vect& v2) const {
    return this != &v2 && (x != v2.x || y != v2.y);  // applying de morgan laws to the negated operator==
}

// external operators (friends)

Vect operator*(double s, const Vect& v) { return v.mult(s); }

Vect operator/(double s, const Vect& v) { return v.div(s); }