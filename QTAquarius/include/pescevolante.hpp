#include "organismo.hpp"

#ifndef PESCEVOLANTE_H
#define PESCEVOLANTE_H

class PesceVolante : public Organismo {
   protected:
    virtual void behaviour(Aquarius*) override;

   public:
    PesceVolante(const Vect2D&, const std::string&);

    // new pure virtual
    virtual bool isHungry() const override;
    virtual void eat(Organismo&) override;

    // repeated pure virtual
    virtual PesceVolante* clone() const override;                     // from CartesianObject2D
    virtual bool isInRange(const Vect2D&) const override;      // from Vehicle
    virtual int getValoreNutrizionale() const override;        // from Organismo
    virtual double getVisibility() const override;             // from Organismo
    virtual std::string getType() const override;              // from Organismo
    virtual bool operator==(const Organismo&) const override;  // from Organismo
    virtual bool operator!=(const Organismo&) const override;  // from Organismo
};

#endif
