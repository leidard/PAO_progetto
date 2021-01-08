#include <string>

// #include "cartesianobject2d.hpp"
#include "daycycle.hpp"
#include "stamina.hpp"
#include "vehicle.hpp"

#ifndef FISH_H
#define FISH_H

class Aquarius;

class Fish : public Vehicle {
   private:
    std::string _name;
    bool _awake;
    bool gone;

   protected:
    DayCycle _daycycle;
    Stamina _stamina;
    virtual void behaviour(Aquarius*) override;

   public:
    Fish(const std::string&, unsigned int, unsigned int, double);
    // defined at this level

    bool getIsGone() const;
    void setIsGone();
    void setName(const std::string&);
    const std::string& getName() const;
    void sleep();
    void wakeup();
    bool isAwake() const;
    bool isAsleep() const;
    const Stamina& getStamina() const;  // ritorna una percentuale

    // overrides
    virtual ~Fish();

    // new pure virtual
    virtual bool isHungry() const = 0;
    virtual bool canSleep() const;
    virtual bool canWakeup() const;
    virtual void eat(Fish&) = 0;
    virtual std::string getType() const = 0;
    virtual int getValoreNutrizionale() const = 0;
    virtual double getVisibility() const = 0;
    virtual bool operator==(const Fish&) const = 0;
    virtual bool operator!=(const Fish&) const = 0;

    // repeated pure virtual

    virtual Fish* clone() const override = 0;         // from CartesianObject2D
    virtual bool isInRange(const Vect2D&) const = 0;  // from vehicle
};

#endif
