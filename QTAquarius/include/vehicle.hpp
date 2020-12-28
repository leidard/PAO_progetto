#include "cartesianobject2d.hpp"
#include "vect2d.hpp"
#include "vector.hpp"

#ifndef VEHICLE_H
#define VEHICLE_H

class Vehicle : virtual public CartesianObject2D {
   protected:
    Vect2D _velocity;
    Vect2D _wander;
    double maxSpeed = 4;  // tipo 4
    double maxForce = 1;  // 0 <= x <= 1 ??

    double PURSUIT_forwardSteps = 5;

    double WANDER_MAX_STRENGTH = 5;
    double WANDER_MAX_RATE = 15;
    double WANDER_forwardSteps = 10;
    double wander_strength = 1;  // 0 <= x <= 1 (where 0 is 0 and 1 is WANDER_MAX_STRENGTH)
    double wander_rate = 1;     // 0 <= x <= 1 (where 0 is 0 and 1 is WANDER_MAX_RATE)

    /** 
     * Calculates the behaviour of the vehicle
     * @param acc acceleration from previous step, default = Vect2D(0,0)
     * @return Vect2D the acceleration
    */
    virtual Vect2D behaviour(Vect2D acc = Vect2D()) = 0;

   public:
    Vehicle();
    //Vehicle(double maxSpeed, double maxForce);
    virtual ~Vehicle() = default;

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

    virtual void advance() final;
};

#endif
