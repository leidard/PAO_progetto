#include "cartesianobject2d.hpp"
#include "food.hpp"
#include "vect2d.hpp"
#include "vector.hpp"
#include "vehicle.hpp"

#ifndef FISH_H
#define FISH_H

class Aquarius;

class Fish : public Vehicle, public Food {
   public:
    //Fish(const Vect2D& p);

    virtual Fish* clone() const = 0;

    virtual int getValoreNutrizionale() const = 0;

    virtual Vect2D behaviour(Aquarius* a, Vect2D acc = Vect2D(0, 0)) const override;

    virtual bool isHungry() const = 0;
    virtual bool isTired() const = 0;
    virtual double getVisibility() const = 0;  // again virtual
    virtual bool isInRange(const Vect2D&) const = 0;
    virtual Vect2D flocking() const = 0;
    virtual void reset(); // or eaten
};

#endif
