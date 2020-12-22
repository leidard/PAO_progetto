#include "circle.h"

bool Circle::contains(const Vect2D& point) const {
    return center.distance(point) <= radius;
}
bool Circle::accept(const Visitor& visitor) const {
    visitor.visit(*this);
}