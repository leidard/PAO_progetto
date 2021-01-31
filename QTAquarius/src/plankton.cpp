#include "plankton.hpp"

Plankton::Plankton(const Vect2D& position, const std::string& name) : Organismo(position, 1, .12, name, 10, 25 * 5, 100) {}

std::string Plankton::getSpecie() const{
    return "plankton";
}

