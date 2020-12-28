#include "food.hpp"

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