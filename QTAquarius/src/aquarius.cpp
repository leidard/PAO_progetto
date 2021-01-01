#include "aquarius.hpp"

#include "deepptr.hpp"
#include "food.hpp"
#include "vector.hpp"
#include <thread>
#include <future>

Aquarius::Aquarius(unsigned int width, unsigned int height) : _width(width), _height(height), fish(), food() {}

unsigned int Aquarius::getWidth() const { return _width; }
unsigned int Aquarius::getHeight() const { return _height; }
aq_size Aquarius::getSize() const { return aq_size(_width, _height); }

void Aquarius::setWidth(unsigned int width) { _width = width; }
void Aquarius::setHeight(unsigned int height) { _height = height; }
void Aquarius::setSize(const aq_size& s) {
    _width = s.first;
    _height = s.second;
}

void Aquarius::addFish(Fish* v) {
    fish.push_back(v);
    food.push_back(v);
}

void Aquarius::addFood(Food* f) {
    food.push_back(f);
}

void Aquarius::addVegetale(Vegetale* v) {
    food.push_back(v);
    vegetali.push_back(v);
}

void Aquarius::remFish(Vector<DeepPtr<Fish>>::iterator i) {
    fish.erase(i);  // the pointer to that object will be invalidated

    auto ft = food.begin();
    while (ft < food.end()) ft = (!*ft) ? food.erase(ft) : ft + 1;
}

void Aquarius::remFood(Vector<DeepPtr<Food>>::iterator i) {
    food.erase(i);  // the pointer to that object will be invalidated

    auto it = fish.begin();
    while (it < fish.end()) it = (!*it) ? fish.erase(it) : it + 1;

    // TODO VEGETALE
}

void Aquarius::setSize(unsigned int width, unsigned int height) {
    _width = width;
    _height = height;
}

Vector<DeepPtr<Fish>>& Aquarius::getAllFish() {
    return fish;
}

Vector<DeepPtr<Food>>& Aquarius::getAllFood() {
    return food;
}

#include <vector>
void Aquarius::advance() {
    //std::vector<std::future<void>> futures;

    // calc changes
    for (DeepPtr<Fish>& i : fish) {
        //futures.push_back(std::async(std::launch::async, [&i, this]()->void{if (i) i->advance(this, 0);}));
        if (i) i->advance(this, 0);
    }

    //for (std::future<void>& f: futures) f.get();

    for (auto& i : fish) {
        if (i) i->advance(this, 1);  // apply changes
    }
}
