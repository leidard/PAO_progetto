#include "organismo.hpp"

#ifndef TONNO_H
#define TONNO_H

class Tonno : public Organismo {
protected:
    virtual void behaviour(Aquarius*) override;

public:
    Tonno(const Vect2D&, const std::string & = "");

    // definition of pure virtual
    virtual bool isHungry() const override;

    // repeated pure virtual
    virtual Tonno* clone() const override;                 // from Vehicle
    virtual bool isInRange(const Vect2D&) const override;  // from Vehicle
    virtual int getValoreNutrizionale() const override;    // from Organismo
    virtual std::string getSpecie() const override;       // from Organismo
};

#endif
