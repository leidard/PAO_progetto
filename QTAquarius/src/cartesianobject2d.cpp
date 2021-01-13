#include "cartesianobject2d.hpp"

CartesianObject2D::CartesianObject2D(const Vect2D& p) : _position(p) {}
CartesianObject2D::~CartesianObject2D() = default;

const Vect2D& CartesianObject2D::getPosition() const { return _position; }