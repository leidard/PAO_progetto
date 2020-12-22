
#include "rectangle.h"

#include "fov.h"
#include "vect2d.h"
#include "visitor.h"

Rectangle::Rectangle(const Vect2D& center_point, int width, int height) : FoV(center_point), halfw(width / 2, 0), halfh(0, height / 2) {}
Rectangle::Rectangle(const Vect2D& center_point, const Vect2D& width, const Vect2D& height) : FoV(center_point), halfw(width.getX() / 2, 0), halfh(0, height.getY() / 2) {}
Rectangle::Rectangle(const Rectangle& r) : FoV(r.center), halfw(r.halfw), halfh(r.halfh) {}
Vect2D Rectangle::getHalfW() const { return halfw; }
Vect2D Rectangle::getHalfH() const { return halfh; }
Rectangle Rectangle::nw() const {
    return Rectangle(center - halfw - halfh, halfw, halfh);
}
Rectangle Rectangle::ne() const {
    return Rectangle(center + halfw - halfh, halfw, halfh);
}
Rectangle Rectangle::sw() const {
    return Rectangle(center - halfw + halfh, halfw, halfh);
}
Rectangle Rectangle::se() const {
    return Rectangle(center + halfw + halfh, halfw, halfh);
}
bool Rectangle::contains(const Vect2D& v) const override {
    auto halfsize = halfw + halfh;
    auto bottomleft = center - halfsize;
    auto topright = center + halfsize;
    return v >= bottomleft && v <= topright;
}
bool Rectangle::accept(const Visitor& v) const override {
    return v.visit(*this);
};