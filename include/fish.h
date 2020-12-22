#include "food.h"
#include "vect2d.h"
#include "vehicle.h"

#ifndef FISH_H
#define FISH_H

class Fish : public Vehicle, public Food {
   private:
    Vect2D position;
   public:
    Fish();
    virtual int getValoreNutrizonale() const = 0;
    virtual Vect2D behaviour() const override;
    virtual bool isHungry() const = 0;
    virtual bool isTired() const = 0;
    virtual int getVisibility() const = 0;
};

#endif

Fish::Fish() : Vehicle(), Food() {
}