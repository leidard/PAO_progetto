#include "sardina.hpp"

Sardina::Sardina(const Vect2D& position, const std::string& name) : CartesianObject2D(position), Organismo(name, 50 * 10, 25 * 5, 80) {}

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

bool Sardina::operator==(const Organismo& o) const {
    auto d = dynamic_cast<const Sardina*>(&o);
    return d != nullptr && d == this;
}

bool Sardina::operator!=(const Organismo& o) const {
    auto d = dynamic_cast<const Sardina*>(&o);
    return d == nullptr || d != this;
}

bool Sardina::isHungry() const {
    return _stamina < 2;
}

void Sardina::eat(Organismo&) {
}

Sardina* Sardina::clone() const {
    return new Sardina(*this);
}

int Sardina::getValoreNutrizionale() const {
    return 2;
}

double Sardina::getVisibility() const {
    return 0;  //TO DO
}

bool Sardina::isInRange(const Vect2D& p) const {
    return _position.distance(p) < 80;  //?
}

std::string Sardina::getType() const {
    return "sardina";
}
