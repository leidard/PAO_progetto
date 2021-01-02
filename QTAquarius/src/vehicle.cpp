#include "vehicle.hpp"

#include <cstdlib>

#include "aquarius.hpp"
#include "deepptr.hpp"
#include "vect2d.hpp"

Vehicle::Vehicle() : _velocity(1, 1), _wander(1, 1) {}

Vehicle::~Vehicle() {}

Vect2D Vehicle::getVelocity() const { return _velocity; }

void Vehicle::setPosition(const Vect2D& v) { position = v; }
void Vehicle::setVelocity(const Vect2D& v) { _velocity = v; }

Vect2D Vehicle::seek(const Vect2D& target) const {  // return steering from here to that target (target - location).normalize().mult(maxspeed);
    Vect2D diff = (target - position);
    if (diff.mag() == 0) return Vect2D();
    diff.setMagnitude(maxSpeed);
    return (diff - _velocity).limit(maxForce);
}
double map(double n, double start1, double stop1, double start2, double stop2) {
    auto newval = (n) / (stop1 - start1) * (stop2 - start2) + start2;
    return newval;
}
Vect2D Vehicle::arrive(const Vect2D& target) const {
    Vect2D desired = (target - position);
    double distance = desired.mag();
    if (distance == 0) return Vect2D(0, 0);
    if (distance < 100) {
        desired.setMagnitude(distance / 100 * maxSpeed);
    } else
        desired.setMagnitude(maxSpeed);
    return (desired - _velocity).limit(maxForce);
}

Vect2D Vehicle::flee(const Vect2D& target) const {
    Vect2D desired = (target - position);

    double distance = desired.mag();
    if (distance < 60 && distance > 0) {
        desired.setMagnitude(distance / -60 * -maxSpeed + maxSpeed);
        desired.mult(-1);
    } else
        return Vect2D(0, 0);

    return (desired - _velocity).limit(maxForce);
}
Vect2D Vehicle::pursuit(const Vehicle& v) const {
    return seek(v.position + (v._velocity * PURSUIT_forwardSteps));
}
Vect2D Vehicle::escape(const Vehicle& v) const {
    return flee(v.position + (v._velocity * PURSUIT_forwardSteps));
}
Vect2D Vehicle::wander() {
    int sign = (std::rand() % 2) ? 1 : -1;  // test this
    // if (_wander.mag())
    // _wander.setMagnitude(wander_strength * WANDER_MAX_STRENGTH);
    // _wander.rotate(sign * wander_rate * WANDER_MAX_RATE);

    return seek(position + (_velocity * WANDER_forwardSteps) + _wander);
}

Vect2D Vehicle::stop() const {
    return arrive(position + _velocity.setMagnitude(2));
}

// #include <iostream>
void Vehicle::advance(Aquarius* a, int phase) {  //divide the method with 2 phase triggere within the aquarius
    if (!phase) {
        Vect2D acc = behaviour(a).limit(maxSpeed);
        _computedvelocity = _velocity + acc;
        _computedposition = position + _computedvelocity;
        auto w = a->getWidth();
        auto h = a->getHeight();
        _computedposition.bounds(Vect2D(w + 20, h + 20));
    } else {
        _velocity = _computedvelocity;
        position = _computedposition;
    }
}
