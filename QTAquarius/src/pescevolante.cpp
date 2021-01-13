#include "pescevolante.hpp"

#include "aquarius.hpp"

PesceVolante::PesceVolante(const Vect2D& position, const std::string& name) : CartesianObject2D(position), Organismo(name, 50 * 10, 25 * 5, 80) {}

void PesceVolante::behaviour(Aquarius* a) {
    Vect2D avgloc;
    int count = 0;
    for (auto& f : a->getAllFish()) {
        if (f && &(*f) != this && isInRange(f->getPosition()) && f->getValoreNutrizionale() > getValoreNutrizionale()) {
            // alignment step

            avgloc += f->getPosition();

            count++;
        }
    }
    if (count != 0) {
        avgloc /= count;
        applyForce(flee(avgloc));
    }

    Organismo::behaviour(a);
}

bool PesceVolante::operator==(const Organismo& f) const {
    auto d = dynamic_cast<const PesceVolante*>(&f);
    return d != nullptr && d == this;
}

bool PesceVolante::operator!=(const Organismo& f) const {
    auto d = dynamic_cast<const PesceVolante*>(&f);
    return d == nullptr || d != this;
}

bool PesceVolante::isHungry() const {
    return _stamina < 2;
}

void PesceVolante::eat(Organismo&) {
}

PesceVolante* PesceVolante::clone() const {
    return new PesceVolante(*this);
}

int PesceVolante::getValoreNutrizionale() const {
    return 2;
}

double PesceVolante::getVisibility() const {
    return 0;  //TO DO
}

bool PesceVolante::isInRange(const Vect2D& p) const {
    return _position.distance(p) < 80;  //?
}

std::string PesceVolante::getType() const {
    return "pesce volante";
}
