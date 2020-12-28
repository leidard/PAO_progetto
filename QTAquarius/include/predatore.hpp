#include "fish.hpp"
#include "vect2d.hpp"

#ifndef PREDATORE_H
#define PREDATORE_H

class Predatore : public Fish {
   private:
    DayCycle _daycycle;
    Stamina _stamina;

   public:
    Predatore(const Vect2D&, const std::string& = "no name");

    // overrides
    virtual ~Predatore();  // TODO can delete this??
    virtual Vect2D behaviour(Vect2D acc = Vect2D(0, 0)) override;

    // defined of pure virtual
    virtual bool isHungry() const override;
    virtual bool canSleep() const override;
    virtual bool canWakeup() const override;
    virtual void eat(Vector<DeepPtr<Food>>::iterator) override;

    // repeated pure virtual
    virtual Predatore* clone() const override;             // from CartesianObject2D
    virtual int getValoreNutrizionale() const override;    // from food
    virtual double getVisibility() const override;         // from food
    virtual bool isInRange(const Vect2D&) const override;  // from vehicle
};

#endif
