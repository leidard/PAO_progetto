#include "vect2d.h"

#ifndef FOOD_H
#define FOOD_H

class Food {
   private:
    Vect2D* position;

   public:
    Food(Vect2D position);
    virtual ~Food() = default;
    virtual int getValoreNutrizonale() const = 0;

    bool operator>(const Food&) const;
    bool operator>=(const Food&) const;
    bool operator<(const Food&) const;
    bool operator<=(const Food&) const;
    bool operator==(const Food&) const;
    bool operator!=(const Food&) const;
};

#endif