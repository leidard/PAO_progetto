#include "sardina.hpp"
#include "squalo.hpp"

#ifndef FISHCREATOR_H
#define FISHCREATOR_H

class Predatore;
class Preda;

class FishCreator {
   public:
    Predatore* createSqualo(/* parametri costruzione solitario */);
    Preda* createSardina(/* parametri costruzione membro branco */);
};

#endif