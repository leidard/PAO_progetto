#include "vect2d.h"
#include "visitor.h"

#ifndef FOV_H
#define FOV_H

class Visitor;
class Vehicle;

class FoV {  // visitable
   protected:
   public:
    virtual ~FoV() = default;
    virtual bool contains(const Vehicle&, const Vect2D&) const = 0;
    virtual bool accept(const Visitor&) const = 0;
};

#endif