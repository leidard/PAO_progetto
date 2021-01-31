#include "aquarius.hpp"
#include "organismo.hpp"

#ifndef SARDINA_H
#define SARDINA_H

class Sardina : public Organismo {
   protected:
    virtual void behaviour(Aquarius*) override;

   public:
    Sardina(const Vect2D&, const std::string& = "");

    // new pure virtual
    virtual bool isHungry() const override;

    // repeated pure virtual
    virtual Sardina* clone() const override;               // from CartesianObject2D
    virtual bool isInRange(const Vect2D&) const override;  // from Vehicle
    virtual int getValoreNutrizionale() const override;    // from Organismo
    virtual std::string getSpecie() const override;       // from Organismo
};

#endif
