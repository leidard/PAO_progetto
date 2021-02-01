#include "aquarius.hpp"

const int Aquarius::ORGANISM_LIMIT = 100;

Aquarius::Aquarius(const std::string& name, unsigned int width, unsigned int height) : _name(name), _width(width), _height(height), organismi(), _autorespawn(false) {}

void Aquarius::setName(const std::string& name) { _name = name; } 

const std::string& Aquarius::getName() const { return _name; }

unsigned int Aquarius::getWidth() const { return _width; }
unsigned int Aquarius::getHeight() const { return _height; }
Vect2D Aquarius::getBounds() const { return Vect2D(_width, _height); }

void Aquarius::setSize(unsigned int width, unsigned int height) {
    _width = width;
    _height = height;
}

bool Aquarius::isAutoRespawnEnabled() const { return _autorespawn; }

void Aquarius::enableAutoRespawn() { _autorespawn = true; }
void Aquarius::disableAutoRespawn() { _autorespawn = false; }

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
            if (_autorespawn) {
                auto a = (*it)->clone();
                a->move(Vect2D(_width/2, _height/2));
                *it = a; // it is a new object
            } else {
                it = organismi.erase(it);
            }
        } else {
            (*it)->advance(this, 1);
            it++;
        }
    }
}
