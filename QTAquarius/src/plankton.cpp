#include "plankton.hpp"
#include "aquarius.hpp"

Plankton::Plankton(const Vect2D& position, const std::string& name) : Organismo(position, 1, .12, name, 50 * 60, 50 * 10, 100) {}

void Plankton::behaviour(Aquarius* a) {
    Vect2D avgloc;
    int count = 0;
    for (auto& o : a->getAllOrganismi()) {
        if (o && &(*o) != this && isInRange(o->getPosition()) && o->getValoreNutrizionale() > getValoreNutrizionale()) {
            // alignment step

            avgloc += o->getPosition();

            count++;
        }
    }
    if (count != 0) {
        avgloc /= count;
        applyForce(flee(avgloc));
    }

    return Organismo::behaviour(a);
}

std::string Plankton::getSpecie() const {
    return "plankton";
}

bool Plankton::isInRange(const Vect2D& p) const {
    return getPosition().distance(p) < 50;
}
