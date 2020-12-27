#include "food.hpp"
#include "vect2d.hpp"

#ifndef VEGETALE_H
#define VEGETALE_H

class Vegetale : public Food {
   private:
    double _visibility;

   public:
    Vegetale(const Vect2D&, double);
    virtual ~Vegetale();
    virtual Vegetale* clone() const override;

    virtual int getValoreNutrizionale() const override;
    virtual double getVisibility() const override;
};

#endif