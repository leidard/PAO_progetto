#include "aquarius.hpp"
#include "organismo.hpp"

#ifndef PLANKTON_H
#define PLANKTON_H

class Plankton : virtual public Organismo {
   protected:
    virtual void behaviour(Aquarius*) = 0;

   public:
    Plankton(const Vect2D&, const std::string& = "");
    virtual ~Plankton() = default;

    // new pure virtual
    virtual bool isHungry() const override;
    virtual void eat(Organismo&) override;

    // repeated pure virtual
    virtual Plankton* clone() const = 0;               // from Vehicle
    virtual bool isInRange(const Vect2D&) const override;  // from Vehicle
    virtual int getValoreNutrizionale() const = 0;    // from Organismo
};

#endif
