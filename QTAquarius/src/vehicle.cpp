#include "vehicle.hpp"

#include <cstdlib>

#include "aquarius.hpp"
#include "deepptr.hpp"
#include "vect2d.hpp"

Vehicle::Vehicle(): _wander(Vect2D(2,2)) {}

Vect2D Vehicle::getVelocity() const { return _velocity; }

void Vehicle::setPosition(const Vect2D& v) { position = v; }
void Vehicle::setVelocity(const Vect2D& v) { _velocity = v; }

Vect2D Vehicle::seek(const Vect2D& target) const {  // return steering from here to that target (target - location).normalize().mult(maxspeed);
    // TODO FIND PROBLEM

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
    return Vect2D(0, 0);  // TODO FIX THIS
}

Vect2D Vehicle::flee(const Vect2D& target) const {
    return ((position - target).setMagnitude(-maxSpeed) - _velocity).limit(-maxForce);
}
Vect2D Vehicle::pursuit(const Vehicle& v) const {
    return seek(v.position + (v._velocity * PURSUIT_forwardSteps));
}
#include <iostream>
Vect2D Vehicle::wander() {
    int sign = (std::rand()%2)?1:-1;  // test this

    _wander.setMagnitude(wander_strength * WANDER_MAX_STRENGTH);
    std:: cout << "rotating by: " << sign* wander_rate * WANDER_MAX_RATE << std::endl;
    _wander.rotate( wander_rate * WANDER_MAX_RATE);
    std::cout << position.x() << std::endl;
    return seek(position + (_velocity * WANDER_forwardSteps));
}
#include <iostream>
void Vehicle::advance() {
    Vect2D acc = behaviour();

    _velocity += acc;
    position += _velocity;

    auto w = Aquarius::getInstance()->getWidth();
    auto h = Aquarius::getInstance()->getHeight();
    double diffy = 0;
    double diffx = 0;
    if (position.y() > h) diffy = -h;
    else if (position.y() < 0) diffy = +h;
    if (position.x() > w) diffx = -w;
    else if(position.x() < 0) diffx = +w;

    position += Vect2D(diffx, diffy);
}
