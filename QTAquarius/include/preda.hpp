#include <string>

#include "fish.hpp"
#include "vect2d.hpp"

#ifndef PREDA_H
#define PREDA_H

class Preda : public Fish {
   public:
    Preda(const Vect2D&, const std::string&);

    // overrides
    virtual ~Preda();
    virtual Vect2D behaviour(Aquarius*, Vect2D acc = Vect2D(0, 0)) override;

    // new pure virtual
    virtual bool isHungry() const override;
    virtual void eat(Fish&) override;  // or eaten

    // repeated pure virtual
    virtual Preda* clone() const override;                 // from CartesianObject2D
    virtual bool isInRange(const Vect2D&) const override;  // from Vehicle
    virtual int getValoreNutrizionale() const override;    // from Fish
    virtual double getVisibility() const override;         // from Fish
    virtual std::string getType() const override;          // from Fish
    virtual bool operator==(const Fish&) const override;   // from Fish
    virtual bool operator!=(const Fish&) const override;   // from Fish
};

#endif
