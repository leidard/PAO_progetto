#include "vect2d.h"
#include "visitor.h"

#ifndef FOV_H
#define FOV_H

class FoV {  // visitable
   private:
    Vect2D center;  // everychild has a center

   public:
    FoV();
    FoV(const Vect2D&);
    Vect2D getCenter() const;
    virtual ~FoV() = default;
    virtual bool contains(const Vect2D&) const = 0;  // fov requirement
    virtual bool accept(const Visitor&) const = 0;   // visitable requirement
};

#endif