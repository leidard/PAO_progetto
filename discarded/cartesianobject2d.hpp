#include "vect2d.hpp"

#ifndef CARTESIAN_OBJECT_2D_H
#define CARTESIAN_OBJECT_2D_H

class CartesianObject2D {
   protected:
    Vect2D _position;

   public:
    CartesianObject2D(const Vect2D& p = Vect2D(0, 0));
    virtual ~CartesianObject2D();
    virtual CartesianObject2D* clone() const = 0;
    const Vect2D& getPosition() const;
};

#endif
