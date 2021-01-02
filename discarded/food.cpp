#include "food.hpp"

#include <iostream>
Food::Food() : gone(false) {}
Food::~Food() {}



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
