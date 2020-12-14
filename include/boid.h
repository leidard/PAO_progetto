#include <quadtree.h>
#include <vect.h>

#include <vector>

#ifndef BOID_H
#define BOID_H
class Boid : private Vect {
   private:
    Vect position;
    Vect velocity;
    Vect acceleration;
    double perception;
    double maxSpeed;  // tipo 4
    double maxForce;  // between 0 and 1 ??

   public:
    Boid();
    virtual ~Boid();

    Vect separation(const std::vector<Boid>& boids) const {
    }
    Vect alignment(const std::vector<Boid>& boids) const {
        Vect desired;
        int count = 0;
        for (auto& b : boids) {
            if (distance(b) <= perception && *this != b) {
                desired.add(b.velocity);
                count++;
            }
        }
        if (count > 0) desired.div(count).setMagnitude(maxSpeed);
        return desired;
    }
    Vect cohesion(const std::vector<Boid>& boids) const {
        Vect desired;
        int count = 0;
        for (auto& b : boids) {
            if (distance(b) <= perception && *this != b) {
                desired.add(b);
                count++;
            }
        }
        if (count > 0) desired.div(count).setMagnitude(maxSpeed);
        return desired;
    }

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

    void update(const std::vector<Boid>& boids) {
        Vect steering = alignment(boids).sub(velocity).limit(maxForce);

        acceleration = steering;

        position.add(velocity);
        velocity.add(acceleration);
        uppermoves();
    }
    void update(const Quadtree& boids) {
        Vect steering = alignment(boids).sub(velocity).limit(maxForce);

        acceleration = steering;

        position.add(velocity);
        velocity.add(acceleration);
        uppermoves();
    }
    virtual void uppermoves() = 0;
    bool operator== {}
};

#endif