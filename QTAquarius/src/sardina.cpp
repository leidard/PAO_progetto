#include "sardina.hpp"

Sardina::Sardina(const Vect2D& position, const std::string& name) : Organismo(position, 4, .12, name, 50 * 10, 25 * 5, 80) {}

void Sardina::behaviour(Aquarius* a) {
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

    Organismo::behaviour(a);
}

bool Sardina::isHungry() const {
    return _stamina.getPercentage() < .2;
}

Sardina* Sardina::clone() const {
    return new Sardina(*this);
}

int Sardina::getValoreNutrizionale() const { return 3; }

std::string Sardina::getSpecie() const{
    return "Sardina";
}

bool Sardina::isInRange(const Vect2D& p) const {
    return getPosition().distance(p) < 80;
}
