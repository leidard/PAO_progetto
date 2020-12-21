#include <include/vect.h>
#include <include/vehicle.h>

Vehicle::Vehicle();
Vehicle::Vehicle(const Vehicle&);
virtual Vehicle::~Vehicle();

void Vehicle::setPosition(Vect* v) { position = v; }

Vect Vehicle::getPosition() const;
Vect Vehicle::getVelocity() const;
Vect Vehicle::getAcceleration() const;
Vect Vehicle::getWander() const;

void Vehicle::setPosition(const Vect&);
void Vehicle::setVelocity(const Vect&);
void Vehicle::setAcceleration(const Vect&);

Vect Vehicle::seek(const Vect& target) const {  // return steering from here to that target (target - location).normalize().mult(maxspeed);
    Vect desired = this->position->sub(target).sectMagnitude(maxSpeed);
    Vect steer = desired.sub(velocity).limit(maxForce);
    return steer;
}
Vect Vehicle::flee(const Vect& target) const {
    Vect desired = this->position->sub(target).sectMagnitude(maxSpeed);
    desired.mult(-1);
    Vect steer = desired.sub(velocity).limit(maxForce);
    return steer;
}
Vect Vehicle::pursuit(const Vehicle& v) const {
    return this->seek(v.position->add(v.velocity));
}
Vect Vehicle::arrive(const Vect& target) const {
    Vect desired = (target - *this);
    double distance = desired.mag();
    desired.normalize();
    if (d < 100) {
        double map(d, 0, 100, 0, maxspeed);
    }
}

void Vehicle::avoid(const Vect& target) const;
// This steering behavior anticipates the vehicle's future path as indicated by the white box. The length of the box is a constant time multiplied by the current velocity of the vehicle. To avoid an obstacle, a lateral steering force is applied opposite to the obstacle's center. In addition, a braking (deceleration) force is applied.

Vehicle& Vehicle::setPosition(const Vect&) const;
Vehicle& Vehicle::setVelocity(const Vect&) const;
Vehicle& Vehicle::setAcceleration(const Vect&) const;

Vect Vehicle::seek(const Vect& target) const {
    return target.sub(velocity);
}

Vect Vehicle::flee(const Vect& target) const {
}

Vect Vehicle::desired_separation(const std::vector<Vehicle>& boids) const {
    Vect desired;
    int count = 0;
    for (auto& other : boids) {
        const double d = distance(other);
        if (*this != other && d <= perception) {
            auto diff = Vect::sub(*this, other);
            diff.normalize(); // this???
            diff.div(d * d);
            desired.add(diff);
            count++;
        }
    }
    if (count > 0) desired.div(count).setMagnitude(maxSpeed);
    return desired;
}

Vect Vehicle::desired_alignment(const std::vector<Vehicle>& boids) const {
    Vect desired;
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

Vect Vehicle::desired_cohesion(const std::vector<Vehicle>& boids) const {
    Vect desired;
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
    Vect separation(const Quadtree& qt) const {
    }
    Vect alignment(const Quadtree& qt) const {
        Vect desired;
        auto boids = qt.queryRange(Circle(*this, perception));
        for (auto& b : boids) {
            if (*this != b) {
                desired.add(b.velocity);
            }
        }
        if (boids.size() > 0) desired.div(boids.size()).setMagnitude(maxSpeed);
        return desired;
    }
    Vect cohesion(const Quadtree& qt) const {
    }
    */

/*
        Vect alignment_steering = seek(desired_alignment(boids)).limit(maxForce);
        Vect cohesion_steering = seek(desired_cohesion(boids)).limit(maxForce);
        Vect separation_steering = seek(desired_separation(boids)).limit(maxForce);

        acc.add(alignment_steering);
        acc.add(cohesion_steering);
        acc.add(separation_steering);
    */

virtual Vehicle& Vehicle::update(const std::vector<Vehicle>& boids) const final {
    Vect acc = behaviour();
    Vehicle& b = this->setPosition(this->add(velocity));
    b.setVelocity(acceleration.add(acc));
}