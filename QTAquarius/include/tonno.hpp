#include "organismo.hpp"

#ifndef Tonno_H
#define Tonno_H

class Tonno : public Organismo {
   protected:
    virtual void behaviour(Aquarius*) override;

   public:
    Tonno(const Vect2D&, const std::string& = "");

    // definition of pure virtual
    virtual bool isHungry() const override;
    virtual void eat(Organismo&) override;

    // repeated pure virtual
    virtual Tonno* clone() const override;                 // from CartesianObject2D
    virtual bool isInRange(const Vect2D&) const override;  // from Vehicle
    virtual int getValoreNutrizionale() const override;    // from Organismo
};

#endif
