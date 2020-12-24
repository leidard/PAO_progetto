#include "aquarius.h"

#include "deepptr.h"
#include "food.h"
#include "vector.h"

Aquarius::Aquarius() : fishes(), food() {}

void Aquarius::addFish(Fish* v) {
    fishes.push_back(v);
}
void Aquarius::addFood(Food* f) {
    food.push_back(f);
}

void Aquarius::update() {
    for (auto& v : fishes) {
        v->update(this);
    }
}

const Vector<DeepPtr<Fish>>& Aquarius::getFishes() {
    return fishes;
}

const Vector<DeepPtr<Food>>& Aquarius::getFood() {
    return food;
}