#include "food.hpp"

#include <iostream>
Food::Food() : _gone(false) {}

bool Food::isGone() const { return _gone; }
void Food::setGone() { _gone = true; }

bool Food::operator>(const Food& f) const {
    return this->getValoreNutrizionale() > f.getValoreNutrizionale();
}
bool Food::operator<(const Food& f) const {
    return this->getValoreNutrizionale() < f.getValoreNutrizionale();
}
bool Food::operator>=(const Food& f) const {
    return this->getValoreNutrizionale() >= f.getValoreNutrizionale();
}
bool Food::operator<=(const Food& f) const {
    return this->getValoreNutrizionale() <= f.getValoreNutrizionale();
}
bool Food::operator==(const Food& f) const {
    return this->getValoreNutrizionale() == f.getValoreNutrizionale();
}
bool Food::operator!=(const Food& f) const {
    return this->getValoreNutrizionale() != f.getValoreNutrizionale();
}
