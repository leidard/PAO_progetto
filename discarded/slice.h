#include "fov.h"
#include "vect2d.h"

#ifndef SLICE_H
#define SLICE_H

class Slice : public FoV {
   private:
    double distance;
    double start_angle;
    double end_angle;

   public:
    bool contains(const Vect2D&, const Vect2D&) const override;
    bool accept(const Visitor&) const override;
};

#endif