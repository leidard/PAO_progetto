#include "cartesianobject2d.hpp"

#ifndef VEHICLE_H
#define VEHICLE_H

class Aquarius;

class Vehicle : virtual public CartesianObject2D {
   private:
    Vect2D _acc;
    Vect2D _computedvelocity;
    Vect2D _computedposition;
    Vect2D _velocity;
    Vect2D _wander;

    static const double PURSUIT_forwardSteps;

    static const double WANDER_MAX_STRENGTH;
    static const double WANDER_MAX_RATE;
    static const double WANDER_forwardSteps;
    static const double wander_strength;  // 0 <= x <= 1 (where 0 is 0 and 1 is WANDER_MAX_STRENGTH)
    static const double wander_rate;      // 0 <= x <= 1 (where 0 is 0 and 1 is WANDER_MAX_RATE)

   protected:
    /** 
     * Calculates the behaviour of the vehicle
     * @param Aquarius* aquarius pointer
     * @return Vect2D the acceleration
    */
    virtual void behaviour(Aquarius*) = 0;

   public:
    static const double maxSpeed;  // tipo 4
    static const double maxForce;  // 0 <= x <= 1

    Vehicle();
    virtual ~Vehicle();

    /**
     * Set the force of acceleration
     * @param acc
    */
    void setForce(const Vect2D&);
    /**
     * Add the force of acceleration, to the already calculated one 
     * @param acc
     * @param weight
    */
    void applyForce(const Vect2D&, const double& = 1);

    const Vect2D& getVelocity() const;

    // utility functions to move around
    Vect2D seek(const Vect2D&) const;      // seek for that point
    Vect2D arrive(const Vect2D&) const;    // arrive at that point
    Vect2D flee(const Vect2D&) const;      // run from that point
    Vect2D pursuit(const Vehicle&) const;  // follow a vehicle
    Vect2D escape(const Vehicle&) const;   // run from a vehicle
    Vect2D wander();                       // wander around
    Vect2D stop() const;                   // stop the vehicle
    Vect2D stayWithinBorders(const Vect2D&, const unsigned int distance) const;

    // pure virtual
    virtual Vehicle* clone() const = 0;
    virtual bool isInRange(const Vect2D& v) const = 0;

    //
    virtual void advance(Aquarius* a, int phase) final;
};

#endif
