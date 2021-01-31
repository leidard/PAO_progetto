#include "phytoplankton.hpp"

Phytoplankton::Phytoplankton(const Vect2D& position, const std::string& name) : Plankton(position, name) {}

void Phytoplankton::behaviour(Aquarius *){
    _daycycle++;  //increase progress
    if (isAsleep()) {
       _stamina -= 1 / 50.0;; //consuma energia mentre dorme
        if (canWakeup())
            wakeup();
        return;
    }

    // è sveglio
    if (_stamina <= 0) { //starved to death
        setGone();
        return;
    }

    if (canSleep()) {  // può dormire?
        sleep();       // dorme
        return;  // turno finito
    }

    // è sveglio e non può dormire
    if (isHungry()) {
        _stamina+= 1 / 50.0;; // se ha fame fa fotosintesi
    }
}


bool Phytoplankton::isHungry() const{
    return _stamina.getPercentage() < 1;
}

std::string Phytoplankton::getSpecie() const{
    return "Phyto" + Plankton::getSpecie();
}

Phytoplankton* Phytoplankton::clone() const{
    return new Phytoplankton(*this);
}

bool Phytoplankton::isInRange(const Vect2D & p) const{
    return getPosition().distance(p) < 50;
}

int Phytoplankton::getValoreNutrizionale() const{
    return 1;
}


