#include "preda.hpp"

#include "aquarius.hpp"
#include "cartesianobject2d.hpp"
#include "deepptr.hpp"
#include "fish.hpp"
#include "vector.hpp"

Preda::Preda(const Vect2D& position, const std::string& name) : CartesianObject2D(position), Fish(name, 50 * 10, 25 * 5, 80) {}

Preda::~Preda() {}

Vect2D Preda::behaviour(Aquarius* a, Vect2D acc) {
    Vect2D avgloc;
    int count = 0;
    for (auto& f : a->getAllFish()) {
        if (f && f.get() != this && isInRange(f->getPosition()) && f->getValoreNutrizionale() > getValoreNutrizionale()) {
            // alignment step

            avgloc += f->getPosition();

            count++;
        }
    }
    if (count != 0) {
        avgloc /= count;  // separation ora é la posizione media

        Vect2D separation = flee(avgloc).limit(.8);

        acc += separation;
    }
    return Fish::behaviour(a, acc);
}
bool Preda::operator==(const Fish& f) const {
    auto d = dynamic_cast<const Preda*>(&f);
    return d != nullptr && d == this;
}

bool Preda::operator!=(const Fish& f) const {
    auto d = dynamic_cast<const Preda*>(&f);
    return d == nullptr || d != this;
}

bool Preda::isHungry() const {
    return _stamina < 2;
}

void Preda::eat(Fish&) {
}

Preda* Preda::clone() const {
    return new Preda(*this);
}

int Preda::getValoreNutrizionale() const {
    return 2;
}

double Preda::getVisibility() const {
    return 0;  //TO DO
}

bool Preda::isInRange(const Vect2D& p) const {
    return position.distance(p) < 80;  //?
}

std::string Preda::getType() const {
    return "preda";
}
