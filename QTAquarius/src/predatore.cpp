#include "predatore.hpp"

#include <string>

#include "aquarius.hpp"
#include "daycycle.hpp"
#include "deepptr.hpp"
#include "stamina.hpp"
#include "vect2d.hpp"

Predatore::Predatore(const Vect2D& position, const std::string& name) : CartesianObject2D(position), Fish(name), _daycycle(25 * 30, 25 * 5), _stamina(10) {
}

// overrides
Predatore::~Predatore() = default;
Vect2D Predatore::behaviour(Vect2D acc) {
    return Fish::behaviour(acc);
}

// defined of pure virtual
bool Predatore::isHungry() const {
    // TODO aggiungere robe strane
    return false;
    //return _stamina < 0.4;
}
bool Predatore::canSleep() const { return false; }
bool Predatore::canWakeup() const { return true; }
void Predatore::eat(Vector<DeepPtr<Food>>::iterator it) {
    _daycycle += 20;
    _stamina += (*it)->getValoreNutrizionale();

    Aquarius::getInstance()->remFood(it);
}

// repeated pure virtual
Predatore* Predatore::clone() const { return new Predatore(*this); }  // from CartesianObject2D
int Predatore::getValoreNutrizionale() const { return 3; }            // from food
double Predatore::getVisibility() const {
    return .2;
}  // from food
bool Predatore::isInRange(const Vect2D& p) const { return position.distance(p) < 60; }  // from vehicle
