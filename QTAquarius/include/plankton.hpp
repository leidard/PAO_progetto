#include "organismo.hpp"

#ifndef PLANKTON_H
#define PLANKTON_H

class Plankton : public Organismo {
protected:
    virtual void behaviour(Aquarius*) override;

public:
    Plankton(const Vect2D&, const std::string & = "");
    virtual ~Plankton() = default;
    virtual std::string getSpecie() const override;
    virtual bool isInRange(const Vect2D&) const override;        // from Vehicle

    // repeated pure virtual
    virtual Plankton* clone() const override = 0;                // from Vehicle
    virtual int getValoreNutrizionale() const override = 0;      // from Organismo
    virtual bool isHungry() const override = 0;                  // from Organismo
};

#endif
