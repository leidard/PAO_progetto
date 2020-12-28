#include <string>

#include "fish.hpp"
#include "vect2d.hpp"

#ifndef PREDA_H
#define PREDA_H

class DayCycle;
class Stamina;

class Preda : public Fish {
   public:
    Preda(const Vect2D&, const std::string&);

    // overrides
    virtual ~Preda();
    virtual Vect2D behaviour(Vect2D acc = Vect2D(0, 0)) override;

    // new pure virtual
    virtual bool isHungry() const override;
    virtual bool canSleep() const override;
    virtual bool canWakeup() const override;
    virtual void eat(Vector<DeepPtr<Food>>::iterator) override;  // or eaten

    // repeated pure virtual
    virtual Preda* clone() const override;                 // from CartesianObject2D
    virtual int getValoreNutrizionale() const override;    // from food
    virtual double getVisibility() const override;         // from food
    virtual bool isInRange(const Vect2D&) const override;  // from vehicle
};

#endif
