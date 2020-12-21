#include <vect.h>
#include <visitor.h>

#ifndef FOV_H
#define FOV_H

class FoV {  // visitable
   private:
    Vect center;  // everychild has a center

   public:
    FoV();
    FoV(const Vect&);
    Vect getCenter() const;
    virtual ~FoV() = default;
    virtual bool contains(const Vect&) const = 0;   // fov requirement
    virtual bool accept(const Visitor&) const = 0;  // visitable requirement
};

#endif