#include "aquarius.h"

#include "deepptr.h"
#include "food.h"
#include "vector.h"
#include "vehicle.h"

Aquarius::Aquarius() : vehicles(), food() {}
Aquarius::Aquarius(const Aquarius&) {}

void Aquarius::addVehicle(Vehicle* v) {
    vehicles.push_back(DeepPtr<Vehicle>(v));
}
void Aquarius::addFood(Food* f) {
    food.push_back(DeepPtr<Food>(f));
}

void Aquarius::update() {
    for (auto& v : vehicles) {
        v->update(vehicles, food);
    }
}