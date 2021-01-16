#include "tonno.hpp"

#include "aquarius.hpp"

Tonno::Tonno(const Vect2D& position, const std::string& name) : CartesianObject2D(position), Organismo(name, 50 * 10, 150, 100) {}

// overrides

void Tonno::behaviour(Aquarius* a) {
    Vect2D alignement;
    Vect2D separation;
    Vect2D cohesion;
    int count = 0;
    for (auto& o : a->getAllOrganismi()) {
        if (o && &(*o) != this && isInRange(o->getPosition())) {
            // alignment step
            alignement += o->getVelocity();

            // separation step
            Vect2D diff = _position - o->getPosition();
            double d = diff.mag();
            if (d != 0)
                diff.div(d * d);
            separation += diff;

            // cohesion step
            cohesion += o->getPosition();

            count++;
        }
    }
    if (count != 0) {
        alignement /= count;
        separation /= count;
        cohesion /= count;

        alignement.setMagnitude(maxSpeed);
        alignement.rem(getVelocity());
        alignement.limit(.8);

        separation.setMagnitude(maxSpeed);
        separation.rem(getVelocity());
        separation.limit(.8);

        cohesion.rem(_position);
        cohesion.setMagnitude(maxSpeed);
        cohesion.rem(getVelocity());
        cohesion.limit(.8);

        applyForce(alignement);
        applyForce(separation, .3);
        applyForce(cohesion, .3);
    }
    Organismo::behaviour(a);
}

bool Tonno::operator==(const Organismo& o) const {
    auto d = dynamic_cast<const Tonno*>(&o);
    return d != nullptr && d == this;
}

bool Tonno::operator!=(const Organismo& o) const {
    auto d = dynamic_cast<const Tonno*>(&o);
    return d == nullptr || d != this;
}

// defined of pure virtual
bool Tonno::isHungry() const {
    return _stamina < 0.4;
}

void Tonno::eat(Organismo& o) {
    _daycycle += 20;
    o.setGone();
    /* if (_stamina.getVal() + o.getValoreNutrizionale() > _stamina.getMax())  //stamina cant exceed its maximum
        _stamina.setValToMax();
    else
        _stamina += o.getValoreNutrizionale();*/
}

// repeated pure virtual
Tonno* Tonno::clone() const { return new Tonno(*this); }  // from CartesianObject2D

int Tonno::getValoreNutrizionale() const { return 3; }  // from Organismo

double Tonno::getVisibility() const {
    return .2;
}

bool Tonno::isInRange(const Vect2D& p) const {
    return _position.distance(p) < 100;  //&& _velocity.angleBetweenRad(p) < M_PI;
}  // from Vehicle

std::string Tonno::getType() const {
    return "tonno";
}  // from Organismo
