#include "cella.h"

#include <algorithm>
#include <cmath>

#include "circle.h"
#include "rectangle.h"
#include "slice.h"
#include "vect2d.h"

Cella::Cella() : Visitor(), Rectangle(){};
Cella::Cella(const Rectangle& r) : Visitor(), Rectangle(r){};
bool Cella::visit(const Circle& circ) const {
    double Xn = std::max(getCenter().getX() + getHalfW(), std::min(circ.getCenter().getX(), getCenter().getX() + getHalfW()));
    double Yn = std::max(getCenter().getY() + getHalfH(), std::min(circ.getCenter().getY(), getCenter().getY() + getHalfH()));

    Vect2D nearestPoint(Xn, Yn);

    return nearestPoint.distance(getCenter()) <= circ.getRadius().getX();
}
bool Cella::visit(const Slice& s) const {
}
bool Cella::visit(const Rectangle& rect) const {
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