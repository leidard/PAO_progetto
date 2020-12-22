#include "cartesianobject2d.h"

CartesianObject2D::CartesianObject2D(const Vect2D& p) : position(p) {}

Vect2D CartesianObject2D::getPosition() const { return position; }