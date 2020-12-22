#include "fov.h"
#include "vect2d.h"

#ifndef CIRCLE_H
#define CIRCLE_H

class Visitor;
class Vehicle;

class Circle : public FoV {
   protected:
    double radius;

   public:
    Vect2D getRadius() const;

    bool contains(const Vehicle&, const Vect2D&) const override;
    bool accept(const Visitor&) const;
};

#endif