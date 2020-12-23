#include "cartesianobject2d.h"
#include "vect2d.h"

#ifndef FOOD_H
#define FOOD_H

class Food : virtual public CartesianObject2D {
   public:
    virtual ~Food() = default;
    virtual int getValoreNutrizonale() const = 0;
    virtual double getVisibility() const = 0;

    virtual Food* clone() const = 0;

    bool operator>(const Food&) const;
    bool operator>=(const Food&) const;
    bool operator<(const Food&) const;
    bool operator<=(const Food&) const;
    bool operator==(const Food&) const;
    bool operator!=(const Food&) const;
};

#endif