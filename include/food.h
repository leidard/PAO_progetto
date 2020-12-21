#include <vect.h>

#ifndef FOOD_H
#define FOOD_H

class Food {
   private:
    Vect* position;

   public:
    Food(Vect position);
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