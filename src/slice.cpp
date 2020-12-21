#include "include/slice.h"
#include <include/vect.h>
#include <include/visitor.h>

bool Slice::contains(const Vect& point) const override{
    Vect d = point.distance(this->getCenter());
    

    return d.mag() < this->p
    
};

bool Slice::accept(const Visitor& v) const override {
    return v.visit(*this);
};