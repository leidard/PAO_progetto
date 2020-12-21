#include <include/cella.h>
#include <include/circle.h>
#include <include/rectangle.h>
#include <include/slice.h>
#include <include/vect.h>

#include <cmath>

Cella::Cella() : Visitor(), Rectangle(){};
Cella::Cella(const Rectangle& r) : Visitor(), Rectangle(r){};
bool Cella::visit(const Circle& circ) const override {
    double Xn = std::max(getCenter().getX() + getHalfW(), std::min(circ.getCenter().getX(), getCenter().getX() + getHalfW()));
    double Yn = std::max(getCenter().getY() + getHalfH(), std::min(circ.getCenter().getY(), getCenter().getY() + getHalfH()));

    Vect nearestPoint(Xn, Yn);

    return nearestPoint.distance(center) <= circ.getRadius().getX();
}
bool Cella::visit(const Slice& s) const override {
}
bool Cella::visit(const Rectangle& rect) const override {
    auto min1 = center - halfw - halfh;
    auto max1 = center + halfw + halfh;
    auto min2 = rect.center - rect.halfw - rect.halfh;
    auto max2 = rect.center + rect.halfw + rect.halfh;

    // the smaller coord of this has to be lteq the maximum coord of the other
    // the maximum coord of this has to be gt   the minimum coord of the other
    return min1 <= max2 &&
           max1 > min2;
}
Cella Cella::nw() const {
    return Cella(Rectangle::nw());
}
Cella Cella::ne() const {
    return Cella(Rectangle::ne());
}
Cella Cella::sw() const {
    return Cella(Rectangle::sw());
}
Cella Cella::se() const {
    return Cella(Rectangle::se());
}