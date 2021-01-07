#include "fish.hpp"

#include "aquarius.hpp"
#include "daycycle.hpp"
#include "deepptr.hpp"
#include "stamina.hpp"
#include "vector.hpp"

Fish::Fish(const std::string& name, unsigned int a, unsigned int s, double stam) : _name(name), _awake(true), gone(false), _daycycle(a, s), _stamina(stam) {}

Fish::~Fish() {}

bool Fish::getIsGone() const { return gone; }
void Fish::setIsGone() { gone = true; }
void Fish::setName(const std::string& name) { _name = name; }
const std::string& Fish::getName() const { return _name; }
const Stamina& Fish::getStamina() const { return _stamina; }
void Fish::sleep() { _awake = false; }
void Fish::wakeup() { _awake = true; }
bool Fish::isAwake() const { return _awake; }
bool Fish::isAsleep() const { return !_awake; }

bool Fish::canSleep() const {
    return _daycycle.isNight();
}

bool Fish::canWakeup() const {
    return _daycycle.isDay();
}

// Vect2D Fish::behaviour(Aquarius* a, Vect2D acc) {
//     _daycycle++;  //increase progress
//     if (isAsleep()) {
//         if (canWakeup())
//             wakeup();
//         setForce(stop());
//         return stop();
//     }
//     // é sveglio
//     _stamina -= 1 / 50.0;
//     if (_stamina <= 0) {
//         setIsGone();
//         return stop();
//     }                   //starved to death
//     if (canSleep()) {   // puó dormire?
//         sleep();        // dorme
//         return stop();  // turno finito
//     }
//     // é sveglio e non puó dormire
//     if (isHungry()) {  // ha fame? then cerca cibo, mira verso il cibo con nuova accelerazione != acc parametro
//         Fish* candidato = nullptr;
//         double mindist = 0;
//         for (auto& f : a->getAllFish()) {
//             if (*this != *f && f->getValoreNutrizionale() < getValoreNutrizionale() && isInRange(f->getPosition())) {
//                 if (!candidato || Vect2D::distance(position, f->getPosition()) < mindist) {
//                     mindist = Vect2D::distance(position, f->getPosition());
//                     candidato = &*f;
//                 }
//             }
//         }
//         if (candidato != nullptr) {
//             if (mindist < getVelocity().mag()) eat(*candidato);
//             return pursuit(*candidato);
//         }
//     }
//     // é sveglio, non puó dormire, non ha fame || non ha trovato cibo
//     // quindi vaga a caso
//     return acc + wander().mult(.2);
// }

void Fish::behaviour(Aquarius* a) {
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
        setIsGone();
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
        Fish* candidato = nullptr;
        double mindist = 0;
        for (auto& f : a->getAllFish()) {
            if (*this != *f && f->getValoreNutrizionale() < getValoreNutrizionale() && isInRange(f->getPosition())) {
                if (!candidato || Vect2D::distance(position, f->getPosition()) < mindist) {
                    mindist = Vect2D::distance(position, f->getPosition());
                    candidato = &*f;
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
/*
Vect2D Vehicle::desired_separation(const std::vector<Vehicle>& boids) const {
    Vect2D desired;
    int count = 0;
    for (auto& other : boids) {
        const double d = distance(other);
        if (*this != other && d <= perception) {
            auto diff = Vect2D::sub(*this, other);
            diff.normalize();  // this???
            diff.div(d * d);
            desired.add(diff);
            count++;
        }
    }
    if (count > 0) desired.div(count).setMagnitude(maxSpeed);
    return desired;
}

Vect2D Vehicle::desired_alignment(const std::vector<Vehicle>& boids) const {
    Vect2D desired;
    int count = 0;
    for (auto& b : boids) {
        if (*this != b && distance(b) <= perception) {
            desired.add(b.velocity);
            count++;
        }
    }
    if (count > 0) desired.div(count).setMagnitude(maxSpeed);
    return desired;
}

Vect2D Vehicle::desired_cohesion(const std::vector<Vehicle>& boids) const {
    Vect2D desired;
    int count = 0;
    for (auto& b : boids)
        if (*this != b && distance(b) <= perception) {
            desired.add(b);
            count++;
        }

    if (count > 0) desired.div(count).sub(*this).setMagnitude(maxSpeed);
    return desired;
}


    Vect2D separation(const Quadtree& qt) const {
    }
    Vect2D alignment(const Quadtree& qt) const {
        Vect2D desired;
        auto boids = qt.queryRange(Circle(*this, perception));
        for (auto& b : boids) {
            if (*this != b) {
                desired.add(b.velocity);
            }
        }
        if (boids.size() > 0) desired.div(boids.size()).setMagnitude(maxSpeed);
        return desired;
    }
    Vect2D cohesion(const Quadtree& qt) const {
    }
    */

/*
        Vect2D alignment_steering = seek(desired_alignment(boids)).limit(maxForce);
        Vect2D cohesion_steering = seek(desired_cohesion(boids)).limit(maxForce);
        Vect2D separation_steering = seek(desired_separation(boids)).limit(maxForce);

        acc.add(alignment_steering);
        acc.add(cohesion_steering);
        acc.add(separation_steering);
    */
