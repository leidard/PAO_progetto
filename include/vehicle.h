#include <fov.h>
#include <quadtree.h>
#include <vect.h>

#include <vector>

#ifndef VEHICLE_H
#define VEHICLE_H

/*void map(double n, double start1, double stop1, double start2, double stop2) {
    auto newval = (n - start1) / (stop1 - start1) * (stop2 - start2) + start2;
    return newval;
}*/

// return Math.max(Math.min(n, high), low);

class Vehicle {
   private:
    Vect* position;
    Vect velocity;
    Vect acceleration;
    Vect wander;
    FoV perception;
    double maxSpeed;  // tipo 4
    double maxForce;  // between 0 and 1 ??

    /** 
     * Calculates the behaviour of the vehicle
     * @param acc acceleration from previous step, default = Vect(0,0)
     * @return Vect the acceleration
    */
    virtual Vect behaviour(const std::vector<Vehicle>& vehicles, const std::vector<Food>& food, Vect acc = Vect(0, 0)) const = 0;

   public:
    Vehicle();
    Vehicle(const Vehicle&);
    virtual ~Vehicle();
    void setPosition(Vect*);

    Vect getPosition() const;
    Vect getVelocity() const;
    Vect getAcceleration() const;
    Vect getWander() const;

    void setPosition(const Vect&);
    void setVelocity(const Vect&);
    void setAcceleration(const Vect&);

    Vect seek(const Vect&) const;
    Vect arrive(const Vect&) const;
    Vect flee(const Vect&) const;
    Vect avoid(const Vect&) const;  // This steering behavior anticipates the vehicle's future path as indicated by the white box. The length of the box is a constant time multiplied by the current velocity of the vehicle. To avoid an obstacle, a lateral steering force is applied opposite to the obstacle's center. In addition, a braking (deceleration) force is applied.

    Vehicle& setPosition(const Vect&) const;
    Vehicle& setVelocity(const Vect&) const;
    Vehicle& setAcceleration(const Vect&) const;

    Vect desired_separation(const std::vector<Vehicle>&) const;
    Vect desired_alignment(const std::vector<Vehicle>&) const;
    Vect desired_cohesion(const std::vector<Vehicle>&) const;

    virtual Vect update() const final;
};

#endif