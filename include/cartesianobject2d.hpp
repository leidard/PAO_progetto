#include "vect2d.hpp"

#ifndef CARTESIAN_OBJECT_2D_H
#define CARTESIAN_OBJECT_2D_H

class CartesianObject2D {
   protected:
    Vect2D position;

   public:
    CartesianObject2D(const Vect2D& p);
    virtual ~CartesianObject2D() = default;
    virtual CartesianObject2D* clone() const = 0;
    Vect2D getPosition() const;
};

#endif