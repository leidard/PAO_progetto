#include <string>

// #include "cartesianobject2d.hpp"
#include "daycycle.hpp"
#include "deepptr.hpp"
#include "food.hpp"
#include "stamina.hpp"
#include "vect2d.hpp"
#include "vector.hpp"
#include "vehicle.hpp"

#ifndef FISH_H
#define FISH_H

class Aquarius;

class Fish : public Vehicle, public Food {
   private:
    std::string _name;
    bool _awake;

   protected:
    DayCycle _daycycle;
    Stamina _stamina;

   public:
    Fish(const std::string&, unsigned int, unsigned int, double);
    // defined at this level

    void setName(const std::string&);
    const std::string& getName() const;
    void sleep();
    void wakeup();
    bool isAwake() const;
    bool isAsleep() const;

    // overrides
    virtual ~Fish();
    virtual Vect2D behaviour(Aquarius* a, Vect2D acc = Vect2D(0, 0)) override;

    // new pure virtual
    virtual bool isHungry() const = 0;
    virtual bool canSleep() const;
    virtual bool canWakeup() const;
    virtual void eat(Vector<DeepPtr<Food>>::iterator) = 0;
    virtual std::string getType() const = 0;

    // repeated pure virtual
    virtual Fish* clone() const override = 0;                // from CartesianObject2D
    virtual int getValoreNutrizionale() const override = 0;  // from food
    virtual double getVisibility() const = 0;                // from food
    virtual bool isInRange(const Vect2D&) const = 0;         // from vehicle
};

#endif
