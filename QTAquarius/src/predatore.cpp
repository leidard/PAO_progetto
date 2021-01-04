#include "predatore.hpp"

#include <iostream>
#include <string>

#include "aquarius.hpp"
#include "daycycle.hpp"
#include "deepptr.hpp"
#include "stamina.hpp"
#include "vect2d.hpp"

Predatore::Predatore(const Vect2D& position, const std::string& name) : CartesianObject2D(position), Fish(name, 50 * 10, 150, 100) {}

// overrides
Predatore::~Predatore(){};

Vect2D Predatore::behaviour(Aquarius* a, Vect2D acc) {
    Vect2D alignement;
    Vect2D separation;
    Vect2D cohesion;
    int count = 0;
    for (auto& f : a->getAllFish()) {
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
        acc.setMagnitude(maxSpeed);
    }

    return Fish::behaviour(a, acc);
}

bool Predatore::operator==(const Fish& f) const {
    auto d = dynamic_cast<const Predatore*>(&f);
    return d != nullptr && d == this;
}

bool Predatore::operator!=(const Fish& f) const {
    auto d = dynamic_cast<const Predatore*>(&f);
    return d == nullptr || d != this;
}

// defined of pure virtual
bool Predatore::isHungry() const {
    return _stamina < 0.4;
}

void Predatore::eat(Fish& f) {
    _daycycle += 20;
    f.setIsGone();
    /* if (_stamina.getVal() + f.getValoreNutrizionale() > _stamina.getMax())  //stamina cant exceed its maximum
        _stamina.setValToMax();
    else
        _stamina += f.getValoreNutrizionale();*/
}

// repeated pure virtual
Predatore* Predatore::clone() const { return new Predatore(*this); }  // from CartesianObject2D

int Predatore::getValoreNutrizionale() const { return 3; }  // from Fish

double Predatore::getVisibility() const {
    return .2;
}  // from Fish

bool Predatore::isInRange(const Vect2D& p) const {
    return position.distance(p) < 100;  //&& _velocity.angleBetweenRad(p) < M_PI;
}  // from Vehicle

std::string Predatore::getType() const {
    return "predatore";
}  // from Fish
