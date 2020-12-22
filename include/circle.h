#include "fov.h"
#include "vect2d.h"
#include "visitor.h"

#ifndef CIRCLE_H
#define CIRCLE_H

class Circle : public FoV {
   protected:
    Vect2D center;
    double radius;

   public:
    Vect2D getCenter() const;
    Vect2D getRadius() const;

    bool contains(const Vect2D& point) const;
    bool accept(const Visitor& visitor) const;
};

#endif