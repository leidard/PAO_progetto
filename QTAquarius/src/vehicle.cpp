#include "vehicle.hpp"

#include <cstdlib>

#include "aquarius.hpp"

const double Vehicle::DEFAULT_MAXSPEED = 5;
const double Vehicle::DEFAULT_MAXFORCE = .15;
const unsigned int Vehicle::ARRIVE_RADIUS = 100U;
const unsigned int Vehicle::FLEE_RADIUS = 100U;
const unsigned int Vehicle::ESCAPE_STEPSAHEAD = 5U;
const unsigned int Vehicle::PURSUIT_STEPSAHEAD = 5U;
const unsigned int Vehicle::BORDER_DISTANCE = 100U;

const double Vehicle::WANDER_MAX_STRENGTH = 5;
const double Vehicle::WANDER_MAX_RATE = .5;
const double Vehicle::WANDER_STEPSAHEAD = 15;
const double Vehicle::wander_strength = 1;  // 0 <= x <= 1 (where 0 is 0 and 1 is WANDER_MAX_STRENGTH)
const double Vehicle::wander_rate = 1;      // 0 <= x <= 1 (where 0 is 0 and 1 is WANDER_MAX_RATE)

Vehicle::Vehicle(const Vect2D& position, double maximumSpeed, double maximumForce) : maxSpeed(maximumSpeed),
                                                                                     maxForce(maximumForce),
                                                                                     _position(position),
                                                                                     _velocity(1, 1),
                                                                                     _wander(1, 1) {
    _velocity.setMagnitude(maxSpeed);
    _velocity.rotateDeg(std::rand() % 360 - 180);
}

void Vehicle::move(const Vect2D & position){
    _position = position;
}

void Vehicle::setForce(const Vect2D& acc) {
    _acc = acc;
}

void Vehicle::applyForce(const Vect2D& acc, const double& weight) {
    _acc += (acc * weight);
}

const Vect2D& Vehicle::getVelocity() const { return _velocity; }

const Vect2D& Vehicle::getPosition() const { return _position; }

Vect2D Vehicle::seek(const Vect2D& target) const {
    return (target - _position).setMagnitude(maxSpeed).rem(_velocity);
}

Vect2D Vehicle::arrive(const Vect2D& target, unsigned int radius) const {
    Vect2D desired = (target - _position);
    double distance = desired.mag();
    if (distance < radius && distance > 0)
        desired.setMagnitude(distance / radius * maxSpeed);
    else
        desired.setMagnitude(maxSpeed);
    return (desired - _velocity);
}

Vect2D Vehicle::flee(const Vect2D& target, unsigned int radius) const {
    Vect2D desired = (target - _position);

    double distance = desired.mag();
    if (distance < radius && distance > 0) {
        desired.setMagnitude(distance / -radius * -maxSpeed + maxSpeed);
        desired.mult(-1);
    } else
        return Vect2D::ZERO;

    return (desired - _velocity);
}

Vect2D Vehicle::pursuit(const Vehicle& v, unsigned int stepsAhead) const {
    return seek(v._position + (v._velocity * stepsAhead));
}

Vect2D Vehicle::escape(const Vehicle& v, unsigned int stepsAhead) const {
    return flee(v._position + (v._velocity * stepsAhead));
}

Vect2D Vehicle::wander() {
    int sign = (std::rand() % 2) ? 1 : -1;  // test this

    _wander.setMagnitude(Vehicle::wander_strength * Vehicle::WANDER_MAX_STRENGTH);
    _wander.rotateRad(sign * Vehicle::wander_rate * Vehicle::WANDER_MAX_RATE);

    return seek(_position + (_velocity * Vehicle::WANDER_STEPSAHEAD) + _wander);
}

Vect2D Vehicle::stop() const {
    return _velocity * (-maxForce);
}

Vect2D Vehicle::stayWithinBorders(const Vect2D& size, unsigned int distance) const {
    Vect2D avoid;
    double d = 0.0;

    // top
    d = _position.y();
    if (d < distance && d > 0) {
        d /= d * d;
        avoid += Vect2D(0, d);
    }

    // left
    d = _position.x();
    if (d < distance && d > 0) {
        d /= d * d;
        avoid += Vect2D(d, 0);
    }

    // right
    d = size.x() - _position.x();
    if (d < distance && d > 0) {
        d /= d * d;
        avoid += Vect2D(-d, 0);
    }

    // bottom
    d = size.y() - _position.y();
    if (d < distance && d > 0) {
        d /= d * d;
        avoid += Vect2D(0, -d);
    }

    if (avoid != Vect2D::ZERO)
        return avoid.div(4).setMagnitude(maxSpeed).rem(_velocity);
    else
        return avoid;
}

void Vehicle::advance(Aquarius* a, int phase) {  //divide the method with 2 phase triggere within the aquarius
    if (!phase) {
        this->behaviour(a);
        applyForce(stayWithinBorders(a->getBounds()));
        _acc.limit(maxForce);
    } else {
        _velocity += _acc;
        _velocity.limit(maxSpeed);
        _position += _velocity;
        _position.bounds(a->getBounds());
        _acc.reset();
    }
}
