#include <cmath>

#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle : public FoV {
   private:
    double halfw;  // w / 2
    double halfh;  // h / 2

   public:
    Rectangle() : FoV(), halfw(), halfh(){};
    Rectangle(const Vect& center_point, int width, int height) : FoV(center_point), halfw(width / 2), halfh(height / 2) {}
    Rectangle(const Rectangle& r) : FoV(r.center), halfw(r.halfw), halfh(r.halfh) {}

    double getHalfW() const;
    double getHalfH() const;

    Rectangle nw() const;
    Rectangle ne() const;
    Rectangle sw() const;
    Rectangle se() const;
    bool contains(const Vect& v) const override;
    bool accept(const Visitor& dispatcher) const override;
};

#endif