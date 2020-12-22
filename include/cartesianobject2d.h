#include "vect2d.h"

#ifndef CARTESIAN_OBJECT_2D
#define CARTESIAN_OBJECT_2D

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