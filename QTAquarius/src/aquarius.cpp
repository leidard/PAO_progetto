#include "aquarius.hpp"

Aquarius::Aquarius(unsigned int width, unsigned int height) : _width(width), _height(height), organismi() {}

unsigned int Aquarius::getWidth() const { return _width; }
unsigned int Aquarius::getHeight() const { return _height; }

void Aquarius::setWidth(unsigned int width) { _width = width; }
void Aquarius::setHeight(unsigned int height) { _height = height; }
void Aquarius::setSize(unsigned int width, unsigned int height) {
    _width = width;
    _height = height;
}

void Aquarius::addOrganismo(Organismo* v) {
    // if (organismi.size() > ORGANISMI_LIMIT)
    organismi.push_back(DeepPtr<Organismo>(v));
    // else throw exception???
    // TODO aggiungere eccezione sul limite di organismi raggiunto oppure ritornare un bool con il successo o meno
}

Vector<DeepPtr<Organismo>>& Aquarius::getAllOrganismi() {
    return organismi;
}

void Aquarius::advance() {
    for (auto& i : organismi) {
        i->advance(this, 0);  // calcolate
    }

    for (auto it = organismi.begin(); it < organismi.end();) {
        if ((*it)->isGone()) {
            it = organismi.erase(it);
            std::cout << "eliminato" << std::endl;
        } else {
            (*it)->advance(this, 1);
            it++;
        }
    }
}
