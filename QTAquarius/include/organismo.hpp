#include <string>

// #include "cartesianobject2d.hpp"
#include "daycycle.hpp"
#include "stamina.hpp"
#include "vehicle.hpp"

#ifndef ORGANISMO_H
#define ORGANISMO_H

class Aquarius;

class Organismo : public Vehicle {
   private:
    std::string _name;
    bool _awake;
    bool _gone;

   protected:
    DayCycle _daycycle;
    Stamina _stamina;
    virtual void behaviour(Aquarius*) override;

   public:
    Organismo(const std::string&, unsigned int, unsigned int, double);
    // defined at this level

    bool isGone() const;
    void setGone();
    void setName(const std::string&);
    const std::string& getName() const;
    void sleep();
    void wakeup();
    bool isAwake() const;
    bool isAsleep() const;
    const Stamina& getStamina() const;  // ritorna una percentuale

    // new pure virtual
    virtual bool isHungry() const = 0;
    virtual bool canSleep() const;
    virtual bool canWakeup() const;
    virtual void eat(Organismo&) = 0;
    virtual std::string getType() const = 0;
    virtual int getValoreNutrizionale() const = 0;
    virtual double getVisibility() const = 0;
    virtual bool operator==(const Organismo&) const = 0;  // TODO this??
    virtual bool operator!=(const Organismo&) const = 0;  // TODO this?

    // repeated pure virtual

    virtual Organismo* clone() const override = 0;    // from CartesianObject2D
};

#endif
