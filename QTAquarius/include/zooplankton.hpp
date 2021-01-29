#include "plankton.hpp"

#ifndef ZOOPLANKTON_H
#define ZOOPLANKTON_H

// mangiano i phytoplankton

class ZooPlankton : public Plankton {
   protected:
    virtual void behaviour(Aquarius*) override;

   public:
    ZooPlankton(const Vect2D&, const std::string& = "");

    // new pure virtual
    virtual bool isHungry() const override;

    // repeated pure virtual
    virtual ZooPlankton* clone() const override;         // from Vehicle
    virtual bool isInRange(const Vect2D&) const override;  // from Vehicle
    virtual int getValoreNutrizionale() const override;    // from Organismo
};

#endif
