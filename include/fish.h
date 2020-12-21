#include <food.h>
#include <vect.h>
#include <vehicle.h>

#ifndef FISH_H
#define FISH_H

class Fish : public Vehicle, public Food {
   public:
    Fish();
    virtual int getValoreNutrizonale() const = 0;
    virtual Vect behaviour() const override;
    virtual bool isHungry() const = 0;
    virtual bool isTired() const = 0;
};

Fish::Fish() {
}

#endif