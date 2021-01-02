#include "daycycle.hpp"
#include "fish.hpp"
#include "stamina.hpp"
#include "vect2d.hpp"

#ifndef PREDATORE_H
#define PREDATORE_H
class Aquarius;

class Predatore : public Fish {
   public:
    Predatore(const Vect2D&, const std::string& = "no name");

    // overrides
    virtual ~Predatore();
    virtual Vect2D behaviour(Aquarius* a, Vect2D acc = Vect2D(0, 0)) override;

    // definition of pure virtual
    virtual bool isHungry() const override;
    virtual void eat(const Fish&) override;

    // repeated pure virtual
    virtual Predatore* clone() const override;             // from CartesianObject2D
    virtual int getValoreNutrizionale() const override;    // from Fish
    virtual double getVisibility() const override;         // from Fish
    virtual bool isInRange(const Vect2D&) const override;  // from Vehicle
    virtual std::string getType() const override;          // from Fish
};

#endif
