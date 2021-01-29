#include "plankton.hpp"

#ifndef PHYTOPLANKTON_H
#define PHYTOPLANKTON_H

// stamina incrementa mentre son svegli e decremena nel sonno!!!
// fanno la fotosintesi

class PhytoPlankton : public Plankton {
   protected:
    virtual void behaviour(Aquarius*) override;

   public:
    PhytoPlankton(const Vect2D&, const std::string& = "");

    // new pure virtual
    virtual bool isHungry() const override;

    // repeated pure virtual
    virtual PhytoPlankton* clone() const override;         // from Vehicle
    virtual bool isInRange(const Vect2D&) const override;  // from Vehicle
    virtual int getValoreNutrizionale() const override;    // from Organismo
};

#endif
