#include <include/food.h>
#include <include/quadtree.h>
#include <include/vehicle.h>

#include <vector>
#ifndef AQUARIUS_H
#define AQUARIUS_H

class Aquarius {
   private:
    std::vector<Vehicle> vehicles;
    std::vector<Food> food;

   public:
    Aquarius();
    Aquarius(const Aquarius&);

    void addVehicle(const Vehicle&);
    void addFood(const Vehicle&);

    void update();
};

void Aquarius::addVehicle(const Vehicle& v) {
    vehicles.push_back(v);
}
void Aquarius::update() {
    for (auto& v : vehicles) {
        v.behaviour(vehicles, food);
    }
}

#endif