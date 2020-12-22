#include "slice.h"

#include "vect2d.h"
#include "visitor.h"

// Vect2D direction
// range

/**
 * calculate if Slice contains a 2Dpoint
 * @return true if the point is lt or eq the direction && the angleBetween the direction and the point is lt or eq the range; 
 * false in every other case
 */
bool Slice::contains(const Vect2D& point) const {
    Vect2D diff = point - center;
    double angle = Vect2D::angleBetween(point, Vect(1, 0));
    return (diff.mag() <= distance && <= range);
};

bool Slice::accept(const Visitor& v) const {
    return v.visit(*this);
};