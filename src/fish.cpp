#include "fish.h"

#include "aquarius.h"
#include "deepptr.h"
#include "food.h"
#include "vector.h"

Vect2D Fish::behaviour(Aquarius* a, Vect2D acc) const {
    if (isHungry()) {
        for (auto f : a->getFishes()) {
            if (f->getValoreNutrizionale() < getValoreNutrizionale() && isInRange(f->getPosition())) {
            }
        }
    } else if (isTired()) {
    }
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