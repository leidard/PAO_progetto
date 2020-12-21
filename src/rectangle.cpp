
#include <include/fov.h>
#include <include/rectangle.h>
#include <include/vect.h>
#include <include/visitor.h>

Rectangle::Rectangle(const Vect& center_point, int width, int height) : FoV(center_point), halfw(width / 2, 0), halfh(0, height / 2) {}
Rectangle::Rectangle(const Vect& center_point, const Vect& width, const Vect& height) : FoV(center_point), halfw(width.getX() / 2, 0), halfh(0, height.getY() / 2) {}
Rectangle::Rectangle(const Rectangle& r) : FoV(r.center), halfw(r.halfw), halfh(r.halfh) {}
Vect Rectangle::getHalfW() const { return halfw; }
Vect Rectangle::getHalfH() const { return halfh; }
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
bool Rectangle::contains(const Vect& v) const override {
    auto halfsize = halfw + halfh;
    auto bottomleft = center - halfsize;
    auto topright = center + halfsize;
    return v >= bottomleft && v <= topright;
}
bool Rectangle::accept(const Visitor& v) const override {
    return v.visit(*this);
};