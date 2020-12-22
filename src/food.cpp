#include "food.h"

bool Food::operator>(const Food& f) const {
    return this->getValoreNutrizonale() > f.getValoreNutrizonale();
}
bool Food::operator<(const Food& f) const {
    return this->getValoreNutrizonale() < f.getValoreNutrizonale();
}
bool Food::operator>=(const Food& f) const {
    return this->getValoreNutrizonale() >= f.getValoreNutrizonale();
}
bool Food::operator<=(const Food& f) const {
    return this->getValoreNutrizonale() <= f.getValoreNutrizonale();
}
bool Food::operator==(const Food& f) const {
    return this->getValoreNutrizonale() == f.getValoreNutrizonale();
}
bool Food::operator!=(const Food& f) const {
    return this->getValoreNutrizonale() != f.getValoreNutrizonale();
}