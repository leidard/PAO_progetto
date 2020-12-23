#include "cartesianobject2d.h"
#include "food.h"
#include "vect2d.h"
#include "vector.h"
#include "vehicle.h"

#ifndef FISH_H
#define FISH_H

class Aquarius;

class Fish : public Vehicle, public Food {
   public:
    //Fish(const Vect2D& p);
    Fish(const Fish& f);

    virtual Fish* clone() const = 0;

    virtual int getValoreNutrizionale() const = 0;

    virtual Vect2D behaviour(Aquarius* a, Vect2D acc = Vect2D(0, 0)) const override;

    virtual bool isHungry() const = 0;
    virtual bool isTired() const = 0;
    virtual double getVisibility() const = 0;  // again virtual
    virtual bool isInRange(const Vect2D&) const = 0;
    virtual Vect2D flocking() const = 0;
};

#endif
