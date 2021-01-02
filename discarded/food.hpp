#include "cartesianobject2d.hpp"
#include "vect2d.hpp"

#ifndef FOOD_H
#define FOOD_H

class Food : virtual public CartesianObject2D {
   private:
    bool gone;

   public:
    Food();
    virtual ~Food();
    virtual int getValoreNutrizionale() const = 0;
    virtual double getVisibility() const = 0;

    virtual Food* clone() const = 0;

    bool getIsGone() const;
    void setIsGone();

    bool operator>(const Food&) const;
    bool operator>=(const Food&) const;
    bool operator<(const Food&) const;
    bool operator<=(const Food&) const;
    bool operator==(const Food&) const;
    bool operator!=(const Food&) const;
};

#endif