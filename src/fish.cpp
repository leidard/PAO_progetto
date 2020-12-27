#include "fish.hpp"

#include "aquarius.hpp"
#include "daycycle.hpp"
#include "deepptr.hpp"
#include "food.hpp"
#include "stamina.hpp"
#include "vector.hpp"

Fish::Fish() : _name(), _awake(true), _daycycle(), _stamina() {}
Fish::Fish(const std::string& name, bool awake, const DayCycle& daycycle, const Stamina& stamina) : Vehicle(), Food(), _name(name), _awake(awake), _daycycle(daycycle), _stamina(stamina) {}
Fish::~Fish() = default;

void Fish::setName(const std::string& name) { _name = name; }
const std::string& Fish::getName() const { return _name; }

void Fish::sleep() { _awake = false; }
void Fish::wakeup() { _awake = true; }
bool Fish::isAwake() const { return _awake; }
bool Fish::isAsleep() const { return !_awake; }
DayCycle& Fish::getDayCycle() { return _daycycle; }
const DayCycle& Fish::getDayCycle() const { return _daycycle; }
Stamina& Fish::getStamina() { return _stamina; }
const Stamina& Fish::getStamina() const { return _stamina; }

Vect2D Fish::behaviour(const Vect2D& acc) {
    if (isAsleep()) {     // sta dormendo
        if (canWakeup())  // puó svegliarsi?
            wakeup();     // then si sveglia else continua a dormire
        return Vect2D();  // turno finito
    }
    // é sveglio
    if (canSleep()) {     // puó dormire?
        sleep();          // dorme
        return Vect2D();  // turno finito
    }
    // é sveglio e non puó dormire
    if (isHungry()) {  // ha fame? then cerca cibo, mira verso il cibo con nuova accelerazione != acc parametro
        for (auto f : Aquarius::getInstance()->getFishes()) {
            if (f->getValoreNutrizionale() < getValoreNutrizionale() && isInRange(f->getPosition())) {
            }
        }
    }
    // é sveglio, non puó dormire, non ha fame || non ha trovato cibo
    // quindi vaga a caso
    return acc + wander();
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