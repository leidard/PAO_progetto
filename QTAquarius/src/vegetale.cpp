#include "vegetale.hpp"

#include "cartesianobject2d.hpp"
#include "vect2d.hpp"

Vegetale::Vegetale(const Vect2D& pos, double visibility) : CartesianObject2D(pos), _visibility(visibility) {}

Vegetale::~Vegetale() = default;

Vegetale* Vegetale::clone() const {
    return new Vegetale(*this);
}

int Vegetale::getValoreNutrizionale() const {
    return 1;
}

double Vegetale::getVisibility() const {
    return _visibility;
}