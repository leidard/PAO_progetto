#include "food.hpp"

#include <iostream>
Food::Food() : gone(false) {}

bool Food::getIsGone() const { return gone; }

void Food::setIsGone() { gone = true; }

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
