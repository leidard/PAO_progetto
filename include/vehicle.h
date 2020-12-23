#include "cartesianobject2d.h"
#include "food.h"
// #include "fov.h"
// #include "quadtree.h"
#include "deepptr.h"
#include "vect2d.h"
#include "vector.h"

#ifndef VEHICLE_H
#define VEHICLE_H

/*void map(double n, double start1, double stop1, double start2, double stop2) {
    auto newval = (n - start1) / (stop1 - start1) * (stop2 - start2) + start2;
    return newval;
}*/

// return Math.max(Math.min(n, high), low);
/**
 * position: (x,y) position in space
 * _velocity: variation of position
 * acceleration: variation of velocity
 */
class Vehicle : virtual public CartesianObject2D {
   protected:
    Vect2D _velocity;
    Vect2D _wander;
    double maxSpeed;  // tipo 4
    double maxForce;  // 0 <= x <= 1 ??

    double PURSUIT_forwardSteps = 5;

    double WANDER_MAX_STRENGTH = 4;
    double WANDER_MAX_RATE = 45;
    double WANDER_forwardSteps = 5;
    double wander_strength = 1;  // 0 <= x <= 1 (where 0 is 0 and 1 is WANDER_MAX_STRENGTH)
    double wander_rate = .6;     // 0 <= x <= 1 (where 0 is 0 and 1 is WANDER_MAX_RATE)
    /** 
     * Calculates the behaviour of the vehicle
     * @param acc acceleration from previous step, default = Vect2D(0,0)
     * @return Vect2D the acceleration
    */
    virtual Vect2D behaviour(const Vector<DeepPtr<Vehicle>>&, const Vector<DeepPtr<Food>>&, Vect2D acc = Vect2D(0, 0)) const = 0;

   public:
    Vehicle(const Vehicle&);
    Vehicle(const Vect2D& position, double maxSpeed, double maxForce);
    virtual ~Vehicle();

    Vehicle& operator=(const Vehicle& v);
    Vect2D getPosition() const;
    Vect2D getVelocity() const;

    void setPosition(const Vect2D&);
    void setVelocity(const Vect2D&);

    Vect2D seek(const Vect2D&) const;
    Vect2D arrive(const Vect2D&) const;
    Vect2D flee(const Vect2D&) const;
    Vect2D pursuit(const Vehicle&) const;
    Vect2D wander();

    virtual Vehicle* clone() const = 0;

    virtual bool isInRange(const Vect2D& v) const = 0;

    virtual void update(const Vector<DeepPtr<Vehicle>>&, const Vector<DeepPtr<Food>>&) final;
};

#endif