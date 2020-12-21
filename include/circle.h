#include <vect.h>
#include <visitor.h>

#ifndef CIRCLE_H
#define CIRCLE_H

class Circle : public FoV {
   protected:
    Vect center;
    double radius;

   public:
    Vect getCenter() const;
    Vect getRadius() const;

    bool contains(const Vect& point) const;
    bool accept(const Visitor& visitor) const;
};

#endif