#include <string>

#include "cartesianobject2d.hpp"
#include "food.hpp"
#include "vect2d.hpp"
#include "vector.hpp"
#include "vehicle.hpp"

#ifndef FISH_H
#define FISH_H

class Fish : public Vehicle, public Food {
   private:
    std::string _name;
    bool _awake;
    DayCycle _daycycle;
    Stamina _stamina;

   public:
    Fish();
    Fish(const std::string&, bool, const DayCycle&, const Stamina&);
    virtual ~Fish();
    // defined at this level

    void setName(const std::string&);
    const std::string& getName() const;
    void sleep();
    void wakeup();
    bool isAwake() const;
    bool isAsleep() const;
    DayCycle& getDayCycle();
    const DayCycle& getDayCycle() const;
    Stamina& getStamina();
    const Stamina& getStamina() const;

    // overrides
    virtual ~Fish();
    virtual Vect2D behaviour(const Vect2D& acc = Vect2D(0, 0)) override;

    // new pure virtual
    virtual std::string getImagePath() const = 0;
    virtual bool isHungry() const = 0;
    virtual bool canSleep() const = 0;
    virtual bool canWakeup() const = 0;
    virtual void reset() const = 0;  // or eaten

    // repeated pure virtual
    virtual Fish* clone() const = 0;                  // from CartesianObject2D
    virtual int getValoreNutrizionale() const = 0;    // from food
    virtual double getVisibility() const = 0;         // from food
    virtual bool isInRange(const Vect2D&) const = 0;  // from vehicle
};

#endif
