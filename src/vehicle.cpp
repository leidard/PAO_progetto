#include "vehicle.h"

#include <cstdlib>

#include "aquarius.h"
#include "deepptr.h"
#include "vect2d.h"

Vect2D Vehicle::getVelocity() const { return _velocity; }

void Vehicle::setPosition(const Vect2D& v) { position = v; }
void Vehicle::setVelocity(const Vect2D& v) { _velocity = v; }

Vect2D Vehicle::seek(const Vect2D& target) const {  // return steering from here to that target (target - location).normalize().mult(maxspeed);
    return ((position - target).setMagnitude(maxSpeed) - _velocity).limit(maxForce);
}
double map(double n, double start1, double stop1, double start2, double stop2) {
    auto newval = (n - start1) / (stop1 - start1) * (stop2 - start2) + start2;
    return newval;
}
Vect2D Vehicle::arrive(const Vect2D& target) const {
    Vect2D desired = (target - position);
    double distance = desired.mag();
    desired.normalize();
    if (distance < 100) {
        map(distance, 0, 100, 0, maxSpeed);
    }
}

Vect2D Vehicle::flee(const Vect2D& target) const {
    return ((position - target).setMagnitude(-maxSpeed) - _velocity).limit(-maxForce);
}
Vect2D Vehicle::pursuit(const Vehicle& v) const {
    return seek(v.position + (v._velocity * PURSUIT_forwardSteps));
}

Vect2D Vehicle::wander() {
    int sign = ((std::rand() >> 0) & 1) * -1;  // test this

    _wander.setMagnitude(wander_strength * WANDER_MAX_STRENGTH);
    _wander.rotate(sign * wander_rate * WANDER_MAX_RATE);

    return seek(position + (_velocity * WANDER_forwardSteps) + _wander);
}

void Vehicle::update(Aquarius* a) {
    Vect2D acc = behaviour(a);

    _velocity += acc;
    position += _velocity;
}