#include "vect2d.hpp"

#ifndef VEHICLE_H
#define VEHICLE_H

class Aquarius;

class Vehicle {
   protected:
    /**
    * maxSpeed is the maximum "pixel per tick"
    */
    const double maxSpeed;

    /**
    * maxForce is how fast the vehicle apply the calculated force to the current velocity each tick
    */
    const double maxForce;

    /** 
     * Calculates the behaviour of the vehicle
     * @param Aquarius* aquarius pointer
    */
    virtual void behaviour(Aquarius*) = 0;

   private:
    Vect2D _position;
    Vect2D _acc;
    Vect2D _velocity;

    Vect2D _wander;

    static const double DEFAULT_MAXSPEED;
    static const double DEFAULT_MAXFORCE;
    static const unsigned int ARRIVE_RADIUS;
    static const unsigned int FLEE_RADIUS;
    static const unsigned int ESCAPE_STEPSAHEAD;
    static const unsigned int PURSUIT_STEPSAHEAD;
    static const unsigned int BORDER_DISTANCE;

    static const double WANDER_MAX_STRENGTH;
    static const double WANDER_MAX_RATE;
    static const double WANDER_STEPSAHEAD;
    static const double wander_strength;  // 0 <= x <= 1 (where 0 is 0 and 1 is WANDER_MAX_STRENGTH)
    static const double wander_rate;      // 0 <= x <= 1 (where 0 is 0 and 1 is WANDER_MAX_RATE)

   public:
    Vehicle(const Vect2D& position, double maxSpeed = Vehicle::DEFAULT_MAXSPEED, double maxForce = Vehicle::DEFAULT_MAXFORCE);

    virtual ~Vehicle() = default;
    virtual Vehicle* clone() const = 0;

    /**
     * Set the force of acceleration
     * (this overwrite the force if already written)
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
    const Vect2D& getPosition() const;

    // utility functions to move around
    Vect2D seek(const Vect2D&) const;                                                  // seek for that point
    Vect2D arrive(const Vect2D&, unsigned int = Vehicle::ARRIVE_RADIUS) const;         // arrive at that point slowing down while approaching
    Vect2D flee(const Vect2D&, unsigned int = Vehicle::FLEE_RADIUS) const;             // run from that point
    Vect2D pursuit(const Vehicle&, unsigned int = Vehicle::PURSUIT_STEPSAHEAD) const;  // follow a vehicle
    Vect2D escape(const Vehicle&, unsigned int = Vehicle::ESCAPE_STEPSAHEAD) const;    // run from a vehicle
    Vect2D wander();                                                                   // wander around
    Vect2D stop() const;                                                               // stop the vehicle
    Vect2D stayWithinBorders(const Vect2D&, unsigned int = Vehicle::BORDER_DISTANCE) const;

    // new pure virtual
    virtual bool isInRange(const Vect2D& v) const = 0;

    // final method doesn't need and won't need override
    virtual void advance(Aquarius* a, int phase) final;
};

#endif
