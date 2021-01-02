#include "predatore.hpp"

#include <iostream>
#include <string>

#include "aquarius.hpp"
#include "daycycle.hpp"
#include "deepptr.hpp"
#include "stamina.hpp"
#include "vect2d.hpp"

Predatore::Predatore(const Vect2D& position, const std::string& name) : CartesianObject2D(position), Fish(name, 1 * 100, 50 * 1, 10){}

// overrides
Predatore::~Predatore() = default;

Vect2D Predatore::behaviour(Aquarius* a, Vect2D acc) {
    auto fish = a->getAllFish();

    Vect2D alignement;
    Vect2D separation;
    Vect2D cohesion;
    int count = 0;
    for (auto& f : fish) {
        if (f && f.get() != this && isInRange(f->getPosition())) {
            // alignment step
            alignement += f->getVelocity();

            // separation step
            Vect2D diff = position - f->getPosition();
            double d = diff.mag();
            if (d != 0)
                diff.div(d * d);
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

            alignement.setMagnitude(maxSpeed);
        alignement.rem(_velocity);
        alignement.limit(.8);

            separation.setMagnitude(maxSpeed);
        separation.rem(_velocity);
        separation.limit(.8);

        cohesion.rem(position);
            cohesion.setMagnitude(maxSpeed);
        cohesion.rem(_velocity);
        cohesion.limit(.8);

        acc += alignement;
        acc += separation * .3;
        acc += cohesion * .3;
        acc.limit(maxSpeed);
    }

    return Fish::behaviour(a, acc);
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
    return _stamina < 0.4;
}

void Predatore::eat(Vector<DeepPtr<Food>>::iterator it) {
    _daycycle += 20;
    if(_stamina.getVal() + (*it)->getValoreNutrizionale() > _stamina.getMax()) //stamina cant exceed its maximum
        _stamina.setValToMax();
    else
        _stamina += (*it)->getValoreNutrizionale();
}

// repeated pure virtual
Predatore* Predatore::clone() const { return new Predatore(*this); }  // from CartesianObject2D

int Predatore::getValoreNutrizionale() const { return 3; }            // from food

double Predatore::getVisibility() const {
    return .2;
}  // from food

bool Predatore::isInRange(const Vect2D& p) const {
    return position.distance(p) < 100;  //&& _velocity.angleBetweenRad(p) < M_PI;
}  // from vehicle

std::string Predatore::getType() const{
    return "predatore";
} // from fish
