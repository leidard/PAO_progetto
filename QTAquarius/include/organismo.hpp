#include <string>

#include "daycycle.hpp"
#include "stamina.hpp"
#include "vehicle.hpp"

#ifndef ORGANISMO_H
#define ORGANISMO_H

class Aquarius;

class Organismo : public Vehicle {
   public:
    static const char ** COOL_NAMES;
   private:
    std::string _name;
    bool _awake;
    bool _gone;

   protected:
    DayCycle _daycycle;
    Stamina _stamina;
    virtual void behaviour(Aquarius*) override;
    virtual void onEatBehaviour();
    //virtual void onAwakeBehaviour();
    //virtual void onSleepBehaviour();

   public:
    Organismo(const Vect2D&, double, double, const std::string&, unsigned int, unsigned int, double);
    Organismo(const Organismo&);
    virtual ~Organismo() = default;
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
    virtual bool canSleep() const;
    virtual bool canWakeup() const;
    virtual bool isHungry() const = 0;
    virtual void eat();
    // repeated pure virtual

    virtual int getValoreNutrizionale() const = 0;
    virtual Organismo* clone() const  override = 0;  // from CartesianObject2D
};

#endif
