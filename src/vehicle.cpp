#include "vehicle.h"

#include "vect2d.h"

Vehicle::Vehicle();
Vehicle::Vehicle(const Vehicle&);
virtual Vehicle::~Vehicle();

void Vehicle::setPosition(Vect2D* v) { position = v; }

Vect2D Vehicle::getPosition() const;
Vect2D Vehicle::getVelocity() const;
Vect2D Vehicle::getAcceleration() const;
Vect2D Vehicle::getWander() const;

void Vehicle::setPosition(const Vect2D&);
void Vehicle::setVelocity(const Vect2D&);
void Vehicle::setAcceleration(const Vect2D&);

Vect2D Vehicle::seek(const Vect2D& target) const {  // return steering from here to that target (target - location).normalize().mult(maxspeed);
    Vect2D desired = this->position->sub(target).sectMagnitude(maxSpeed);
    Vect2D steer = desired.sub(velocity).limit(maxForce);
    return steer;
}
Vect2D Vehicle::flee(const Vect2D& target) const {
    Vect2D desired = this->position->sub(target).sectMagnitude(maxSpeed);
    desired.mult(-1);
    Vect2D steer = desired.sub(velocity).limit(maxForce);
    return steer;
}
Vect2D Vehicle::pursuit(const Vehicle& v) const {
    return this->seek(v.position->add(v.velocity));
}
Vect2D Vehicle::arrive(const Vect2D& target) const {
    Vect2D desired = (target - *this);
    double distance = desired.mag();
    desired.normalize();
    if (d < 100) {
        double map(d, 0, 100, 0, maxspeed);
    }
}

void Vehicle::avoid(const Vect2D& target) const;
// This steering behavior anticipates the vehicle's future path as indicated by the white box. The length of the box is a constant time multiplied by the current velocity of the vehicle. To avoid an obstacle, a lateral steering force is applied opposite to the obstacle's center. In addition, a braking (deceleration) force is applied.

Vehicle& Vehicle::setPosition(const Vect2D&) const;
Vehicle& Vehicle::setVelocity(const Vect2D&) const;
Vehicle& Vehicle::setAcceleration(const Vect2D&) const;

Vect2D Vehicle::seek(const Vect2D& target) const {
    return target.sub(velocity);
}

Vect2D Vehicle::flee(const Vect2D& target) const {
}

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

/*
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

virtual Vehicle& Vehicle::update(const std::vector<Vehicle>& boids) const final {
    Vect2D acc = behaviour();
    Vehicle& b = this->setPosition(this->add(velocity));
    b.setVelocity(acceleration.add(acc));
}