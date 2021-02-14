#include "phytoplankton.hpp"

Phytoplankton::Phytoplankton(const Vect2D& position, const std::string& name) : Plankton(position, name) {}

void Phytoplankton::behaviour(Aquarius* a) {
    _daycycle++;  //increase progress
    if (isAwake()) {
        _stamina += 0.04 * _stamina.getMax(); // fotosintesi
    }
    else {
        _stamina -= 0.02 * _stamina.getMax();;
    }

    return Plankton::behaviour(a);
}


bool Phytoplankton::isHungry() const {
    return false;
}

std::string Phytoplankton::getSpecie() const {
    return "Phyto" + Plankton::getSpecie();
}

Phytoplankton* Phytoplankton::clone() const {
    return new Phytoplankton(*this);
}

int Phytoplankton::getValoreNutrizionale() const {
    return 2;
}


