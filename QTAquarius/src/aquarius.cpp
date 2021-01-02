#include "aquarius.hpp"

#include "deepptr.hpp"
#include "vector.hpp"
// #include <thread>
// #include <future>
#include <iostream>
#include <utility>

Aquarius::Aquarius(unsigned int width, unsigned int height) : _width(width), _height(height), fish() {}

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
    fish.push_back(std::move(DeepPtr<Fish>(v)));
}

void Aquarius::remFish(Vector<DeepPtr<Fish>>::iterator i) {
    fish.erase(i);  // the pointer to that object will be invalidated
}

void Aquarius::setSize(unsigned int width, unsigned int height) {
    _width = width;
    _height = height;
}

Vector<DeepPtr<Fish>>& Aquarius::getAllFish() {
    return fish;
}

void Aquarius::advance() {
    for (auto& i : fish) {
        i->advance(this, 0);  // calcolate
    }

    for (auto it = fish.begin(); it < fish.end();) {
        DeepPtr<Fish>& i = *it;
        if (i->getIsGone())
            it = fish.erase(it);
        else {
            i->advance(this, 1);
            it++;
        }
    }
}
