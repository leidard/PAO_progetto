#include "predatore.hpp"

#include "aquarius.hpp"

Predatore::Predatore(const Vect2D& position, const std::string& name) : CartesianObject2D(position), Fish(name, 50 * 10, 150, 100) {}

// overrides
Predatore::~Predatore() = default;

void Predatore::behaviour(Aquarius* a) {
    Vect2D alignement;
    Vect2D separation;
    Vect2D cohesion;
    int count = 0;
    for (auto& f : a->getAllFish()) {
        if (f && &(*f) != this && isInRange(f->getPosition())) {
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

        alignement.setMagnitude(Vehicle::maxSpeed);
        alignement.rem(getVelocity());
        alignement.limit(.8);

        separation.setMagnitude(Vehicle::maxSpeed);
        separation.rem(getVelocity());
        separation.limit(.8);

        cohesion.rem(position);
        cohesion.setMagnitude(Vehicle::maxSpeed);
        cohesion.rem(getVelocity());
        cohesion.limit(.8);

        applyForce(alignement);
        applyForce(separation, .3);
        applyForce(cohesion, .3);
    }
    Fish::behaviour(a);
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
}

bool Predatore::isInRange(const Vect2D& p) const {
    return position.distance(p) < 100;  //&& _velocity.angleBetweenRad(p) < M_PI;
}  // from Vehicle

std::string Predatore::getType() const {
    return "predatore";
}  // from Fish
