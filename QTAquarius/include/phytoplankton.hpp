#include "plankton.hpp"

#ifndef PHYTOPLANKTON_H
#define PHYTOPLANKTON_H

// stamina incrementa mentre son svegli e decremena nel sonno!!!
// fanno la fotosintesi

class Phytoplankton : public Plankton {
protected:
    virtual void behaviour(Aquarius*) override;

public:
    Phytoplankton(const Vect2D&, const std::string & = "");

    // new pure virtual
    virtual bool isHungry() const override;
    virtual std::string getSpecie() const override;

    // repeated pure virtual
    virtual Phytoplankton* clone() const override;         // from Vehicle
    virtual int getValoreNutrizionale() const override;    // from Organismo
};

#endif
