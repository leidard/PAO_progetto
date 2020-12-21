#include <fov.h>
#include <vect.h>

#ifndef SLICE_H
#define SLICE_H

class Slice : public FoV {
   private:
    Vect direction;
    double range;

   public:
    bool contains(const Vect&) const override;
    bool accept(const Visitor&) const override;
};

#endif