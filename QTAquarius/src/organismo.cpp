#include "organismo.hpp"

#include "aquarius.hpp"

Organismo::Organismo(const std::string& name, unsigned int a, unsigned int s, double stam) : _name(name), _awake(true), _gone(false), _daycycle(a, s), _stamina(stam) {}


bool Organismo::isGone() const { return _gone; }
void Organismo::setGone() { _gone = true; }
void Organismo::setName(const std::string& name) { _name = name; }
const std::string& Organismo::getName() const { return _name; }
const Stamina& Organismo::getStamina() const { return _stamina; }
void Organismo::sleep() { _awake = false; }
void Organismo::wakeup() { _awake = true; }
bool Organismo::isAwake() const { return _awake; }
bool Organismo::isAsleep() const { return !_awake; }

bool Organismo::canSleep() const {
    return _daycycle.isNight();
}

bool Organismo::canWakeup() const {
    return _daycycle.isDay();
}

void Organismo::behaviour(Aquarius* a) {
    _daycycle++;  //increase progress
    if (isAsleep()) {
        if (canWakeup())
            wakeup();
        setForce(stop());
        return;
    }
    // é sveglio
    _stamina -= 1 / 50.0;
    if (_stamina <= 0) {
        setGone();
        setForce(stop());
        return;
    }                  //starved to death
    if (canSleep()) {  // puó dormire?
        sleep();       // dorme
        setForce(stop());
        return;  // turno finito
    }
    // é sveglio e non puó dormire
    if (isHungry()) {  // ha fame? then cerca cibo, mira verso il cibo con nuova accelerazione != acc parametro
        Organismo* candidato = nullptr;
        double mindist = 0;
        for (auto& o : a->getAllOrganismi()) {
            if (*this != *o && o->getValoreNutrizionale() < getValoreNutrizionale() && isInRange(o->getPosition())) {
                if (!candidato || Vect2D::distance(_position, o->getPosition()) < mindist) {
                    mindist = Vect2D::distance(_position, o->getPosition());
                    candidato = &*o;
                }
            }
        }
        if (candidato != nullptr) {
            if (mindist < getVelocity().mag()) eat(*candidato);
            setForce(pursuit(*candidato));
            return;
        }
    }
    // é sveglio, non puó dormire, non ha fame || non ha trovato cibo
    // quindi vaga a caso
    applyForce(wander(), .2);
}
