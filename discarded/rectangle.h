#include <cmath>

#include "fov.h"
#include "vect2d.h"

#ifndef RECTANGLE_H
#define RECTANGLE_H

class Visitor;

class Rectangle : public FoV {
   private:
    double halfw;  // w / 2
    double halfh;  // h / 2

   public:
    Rectangle(const Vect2D& center_point, int width, int height);
    Rectangle(const Rectangle& r);

    double getHalfW() const;
    double getHalfH() const;

    Rectangle nw() const;
    Rectangle ne() const;
    Rectangle sw() const;
    Rectangle se() const;
    bool contains(const Vehicle&, const Vect2D&) const override;
    bool accept(const Visitor& dispatcher) const override;
};

#endif