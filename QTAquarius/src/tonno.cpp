#include "tonno.hpp"

#include "aquarius.hpp"

Tonno::Tonno(const Vect2D& position, const std::string& name) : Organismo(position, 5, .15, name, 50 * 10, 150, 100) {}

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
            Vect2D diff = getPosition() - o->getPosition();
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
        alignement.limit(maxForce);

        separation.setMagnitude(maxSpeed);
        separation.rem(getVelocity());
        separation.limit(maxForce);

        cohesion.rem(getPosition());
        cohesion.setMagnitude(maxSpeed);
        cohesion.rem(getVelocity());
        cohesion.limit(maxForce);

        applyForce(alignement, .9);
        applyForce(separation, .5);
        applyForce(cohesion, .35);
    }
    Organismo::behaviour(a);
}

// defined of pure virtual
bool Tonno::isHungry() const {
    return _stamina.getPercentage() < .4;
}

// repeated pure virtual
Tonno* Tonno::clone() const { return new Tonno(*this); }  // from CartesianObject2D

int Tonno::getValoreNutrizionale() const { return 3; }

std::string Tonno::getSpecie() const {
    return "Tonno";
}  // from Organismo

bool Tonno::isInRange(const Vect2D& p) const {
    return getPosition().distance(p) < 100 && getVelocity().angleBetweenDeg(p) < 150;
}  // from Vehicle
