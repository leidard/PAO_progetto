#include <QColor>

#include "vect2d.hpp"

#ifndef FISHCREATOR_H
#define FISHCREATOR_H

class Predatore;
class Preda;

class FishCreator {
   public:
    Predatore* createPredatore(const Vect2D& pos /* parametri costruzione predatore (solitario) */);
    Preda* createPreda(const Vect2D& pos /* parametri costruzione membro branco */);
};

#endif