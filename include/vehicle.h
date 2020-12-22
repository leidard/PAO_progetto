#include <vector>

#include "fov.h"
#include "quadtree.h"
#include "vect2d.h"

#ifndef VEHICLE_H
#define VEHICLE_H

/*void map(double n, double start1, double stop1, double start2, double stop2) {
    auto newval = (n - start1) / (stop1 - start1) * (stop2 - start2) + start2;
    return newval;
}*/

// return Math.max(Math.min(n, high), low);

class Vehicle {
   private:
    Vect2D* position;
    Vect2D velocity;
    Vect2D acceleration;
    Vect2D wander;
    FoV* perception;
    double maxSpeed;  // tipo 4
    double maxForce;  // between 0 and 1 ??
   public:
    Vehicle();
    Vehicle(const Vehicle&);
    virtual ~Vehicle();
    void setPosition(Vect2D*);

    Vect2D getPosition() const;
    Vect2D getVelocity() const;
    Vect2D getAcceleration() const;
    Vect2D getWander() const;

    void setPosition(const Vect2D&);
    void setVelocity(const Vect2D&);
    void setAcceleration(const Vect2D&);

    Vect2D seek(const Vect2D&) const;
    Vect2D arrive(const Vect2D&) const;
    Vect2D flee(const Vect2D&) const;
    Vect2D avoid(const Vect2D&) const;  // This steering behavior anticipates the vehicle's future path as indicated by the white box. The length of the box is a constant time multiplied by the current velocity of the vehicle. To avoid an obstacle, a lateral steering force is applied opposite to the obstacle's center. In addition, a braking (deceleration) force is applied.

    Vehicle& setPosition(const Vect2D&) const;
    Vehicle& setVelocity(const Vect2D&) const;
    Vehicle& setAcceleration(const Vect2D&) const;

    Vect2D desired_separation(const std::vector<Vehicle>&) const;
    Vect2D desired_alignment(const std::vector<Vehicle>&) const;
    Vect2D desired_cohesion(const std::vector<Vehicle>&) const;

    /** 
     * Calculates the behaviour of the vehicle
     * @param acc acceleration from previous step, default = Vect2D(0,0)
     * @return Vect2D the acceleration
    */
    virtual Vect2D behaviour(const std::vector<Vehicle>& vehicles, const std::vector<Food>& food, Vect2D acc = Vect2D(0, 0)) const = 0;

    virtual Vect2D update() const final;
};

#endif