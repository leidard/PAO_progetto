#include "deepptr.h"
#include "food.h"
// #include "quadtree.h"
#include "vector.h"
#include "vehicle.h"

#ifndef AQUARIUS_H
#define AQUARIUS_H

class Aquarius {
   private:
    Vector<DeepPtr<Vehicle>> vehicles;
    Vector<DeepPtr<Food>> food;

   public:
    Aquarius();
    Aquarius(const Aquarius&);

    void addVehicle(Vehicle*);
    void addFood(Food*);

    void update();
};

void Aquarius::addVehicle(Vehicle* v) {
    vehicles.push_back(DeepPtr<Vehicle>(v));
}
void Aquarius::update() {
    for (auto& v : vehicles) {
        v->update(vehicles, food);
    }
}

#endif