#include "predatore.hpp"

#include <string>
#include <iostream>

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
    Aquarius* a = Aquarius::getInstance();
    auto fish = a->getAllFish();

    Vect2D alignement;
    Vect2D separation;
    Vect2D cohesion;
    int count = 0;
    for (auto& f: fish) {
        if (f && f.get() != this && isInRange(f->getPosition())) {
            // alignment step
            alignement += f->getVelocity();

            // separation step
            Vect2D diff = position - f->getPosition();
            double d = diff.mag();
            if (d != 0)
                diff.div(d*d);
            separation += diff;

            // cohesion step
            cohesion += f->getPosition();

            count++;
        }
    }
    if (count != 0) {
        alignement /= count;
        separation /= count;
        cohesion /= count;

        if (alignement.mag() != 0)
            alignement.setMagnitude(maxSpeed);
        alignement.rem(_velocity);
        alignement.limit(.8);

        if (separation.mag() != 0)
            separation.setMagnitude(maxSpeed);
        separation.rem(_velocity);
        separation.limit(.8);

        cohesion.rem(position);
        if (cohesion.mag() != 0)
            cohesion.setMagnitude(maxSpeed);
        cohesion.rem(_velocity);
        cohesion.limit(.8);

        acc += alignement ;
        acc += separation * .3 ;
        acc += cohesion * .3 ;
        acc.limit(maxSpeed);
    }


    return Fish::behaviour(acc);
}

/*
Vect2D Vehicle::desired_cohesion(const std::vector<Vehicle>& boids) const {
    Vect2D desired;
    int count = 0;
    for (auto& b : boids)
        if (*this != b && distance(b) <= perception) {
            desired.add(b);
            count++;
        }

    if (count > 0) desired.div(count).sub(*this).setMagnitude(maxSpeed);
    return desired;
}*/

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
bool Predatore::isInRange(const Vect2D& p) const {
    return position.distance(p) < 100;//&& _velocity.angleBetweenRad(p) < M_PI;
}  // from vehicle
