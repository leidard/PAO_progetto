#include "fish.hpp"
#include "vect2d.hpp"
#include "daycycle.hpp"
#include "stamina.hpp"

#ifndef PREDATORE_H
#define PREDATORE_H
class Aquarius;

class Predatore : public Fish {
   public:
    Predatore(const Vect2D&, const std::string& = "no name");

    // overrides
    virtual ~Predatore();  // TODO can delete this??
    virtual Vect2D behaviour(Aquarius* a, Vect2D acc = Vect2D(0, 0)) override;

    // defined of pure virtual
    virtual bool isHungry() const override;
    virtual void eat(Vector<DeepPtr<Food>>::iterator) override;

    // repeated pure virtual
    virtual Predatore* clone() const override;             // from CartesianObject2D
    virtual int getValoreNutrizionale() const override;    // from Food
    virtual double getVisibility() const override;         // from Food
    virtual bool isInRange(const Vect2D&) const override;  // from Vehicle
    virtual std::string getType() const override;         // from Fish
};

#endif
