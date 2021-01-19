#include "aquarius.hpp"

const int Aquarius::ORGANISM_LIMIT = 100;

Aquarius::Aquarius(unsigned int width, unsigned int height) : _width(width), _height(height), organismi() {}

unsigned int Aquarius::getWidth() const { return _width; }
unsigned int Aquarius::getHeight() const { return _height; }
Vect2D Aquarius::getBounds() const { return Vect2D(_width, _height); }

void Aquarius::setSize(unsigned int width, unsigned int height) {
    _width = width;
    _height = height;
}

void Aquarius::addOrganismo(Organismo* v) {
    if (organismi.size() < ORGANISM_LIMIT)
        organismi.push_back(DeepPtr<Organismo>(v));
}

bool Aquarius::canAddOrganismo() const { return organismi.size() < ORGANISM_LIMIT; }

Vector<DeepPtr<Organismo>>& Aquarius::getAllOrganismi() {
    return organismi;
}

void Aquarius::advance() {
    for (auto& i : organismi) {
        i->advance(this, 0);  // calcolate
    }
    auto it = organismi.begin();
    while (it != organismi.end()) {
        if ((*it)->isGone()) {
            it = organismi.erase(it);
        } else {
            (*it)->advance(this, 1);
            it++;
        }
    }
}
