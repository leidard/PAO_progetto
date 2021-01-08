#include "aquarius.hpp"

#include "deepptr.hpp"
#include "vector.hpp"

Aquarius::Aquarius(unsigned int width, unsigned int height) : _width(width), _height(height), fish() {}

unsigned int Aquarius::getWidth() const { return _width; }
unsigned int Aquarius::getHeight() const { return _height; }

void Aquarius::setWidth(unsigned int width) { _width = width; }
void Aquarius::setHeight(unsigned int height) { _height = height; }
void Aquarius::setSize(unsigned int width, unsigned int height) {
    _width = width;
    _height = height;
}

void Aquarius::addFish(Fish* v) {
    // if (fish.size() > FISH_LIMIT)
    fish.push_back(DeepPtr<Fish>(v));
    // else throw exception???
    // TODO aggiungere eccezione sul limite di pesci raggiunto oppure ritornare un bool con il successo o meno
}

Vector<DeepPtr<Fish>>& Aquarius::getAllFish() {
    return fish;
}

void Aquarius::advance() {
    for (auto& i : fish) {
        i->advance(this, 0);  // calcolate
    }

    for (auto it = fish.begin(); it < fish.end();) {
        if ((*it)->getIsGone()) {
            it = fish.erase(it);
            std::cout << "eliminato" << std::endl;
        } else {
            (*it)->advance(this, 1);
            it++;
        }
    }
}
