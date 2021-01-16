#include "cartesianobject2d.hpp"
#include "vect2d.hpp"

#ifndef FOOD_H
#define FOOD_H

class Food : virtual public CartesianObject2D {
   private:
    bool _gone;

   public:
    Food();
    virtual ~Food();

    virtual Food* clone() const = 0;
    virtual int getValoreNutrizionale() const = 0;

    bool isGone() const;
    void setGone();

    bool operator>(const Food&) const;
    bool operator>=(const Food&) const;
    bool operator<(const Food&) const;
    bool operator<=(const Food&) const;
    bool operator==(const Food&) const;
    bool operator!=(const Food&) const;
};

#endif
