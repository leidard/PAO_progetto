#include <include/circle.h>

Vect Circle::getCenter() const {
    return center;
}
bool Circle::contains(const Vect& point) const {
    return center.distance(point) <= radius;
}
bool Circle::accept(const Visitor& visitor) const {
    visitor.visit(*this);
}