#include <../include/vect.h>

class Vect {
   private:
    double x, y;

   public:
    Vect(double coord_x, double coord_y) : x(coord_x), y(coord_y) {}
    Vect(const Vect& v) : x(v.x), y(v.y) {}
    double getX() const { return y; }
    double getY() const { return x; }
    Vect getXVect() const { return Vect(x, 0); }
    Vect getYVect() const { return Vect(0, y); }

    // non-const edit functions

    Vect& normalize() {
        *this /= (mag());  // *this /= magnitude()
        return *this;
    }
    Vect& setMagnitude(double m) {
        this->normalize().mult(m);
        return *this;
    }
    Vect& sum(const Vect& v) {
        x += v.x;
        y += v.y;
        return *this;
    }
    Vect& sub(const Vect& v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }
    Vect& mult(double s) {
        x *= s;
        y *= s;
        return *this;
    }
    Vect& div(double s) {
        x /= s;
        y /= s;
        return *this;
    }

    Vect normal() const {
        return *this / (mag());  // *this / magnitude()
    }
    double mag() const {  // modulo (o magnitude)
        return std::sqrt(x * x + y * y);
    }
    double dot(const Vect& v) const {
        return x * v.x + y * v.y;
    }
    double distance(const Vect& v) const {
        return (*this - v).mag();
    }
    double angleBetween(const Vect& v) const {
        return std::acos(this->dot(v) / (this->mag() * v.mag()));
    }
    Vect scalarProjection(const Vect& v) const {
        return v.normal().mult(this->dot(v));
    }

    Vect min(const Vect& v) const {
        return (*this < v) ? *this : v;
    }

    Vect max(const Vect& v) const {
        return (*this > v) ? *this : v;
    }

    Vect operator+(const Vect& v) const {
        return Vect(x + v.x, y + v.y);
    }
    Vect operator-(const Vect& v) const {
        return Vect(x - v.x, y - v.y);
    }
    double operator*(const Vect& v) const {
        return this->dot(v);
    }
    Vect operator*(double n) const {
        return Vect(x * n, y * n);
    }
    double operator/(const Vect& v) const {
        return x / v.x + y / v.y;
    }
    Vect operator/(double n) const {  // can't divide by zero obv
        return Vect(x / n, y / n);
    }

    Vect& operator+=(const Vect& v) {
        x += v.x;
        y += v.y;
        return *this;
    }
    Vect& operator-=(const Vect& v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }
    Vect& operator*=(double n) {  // outside for double side operator scalar * vector and vector * scalar
        return this->mult(n);
    }
    Vect& operator/=(double n) {  // outside for double side operator scalar * vector and vector * scalar
        return this->mult(1 / n);
    }

    bool operator>(const Vect& v2) const {
        return x > v2.x && y > v2.y;
    }
    bool operator>=(const Vect& v2) const {
        return x >= v2.x && y >= v2.y;
    }
    bool operator<(const Vect& v2) const {
        return x < v2.x && y < v2.y;
    }
    bool operator<=(const Vect& v2) const {
        return x <= v2.x && y <= v2.y;
    }
    bool operator==(const Vect& v2) const {
        return x == v2.x && y == v2.y;
    }
    bool operator!=(const Vect& v2) const {
        return x != v2.x || y != v2.y;
    }
};
