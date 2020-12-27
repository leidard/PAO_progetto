#include "middlewares/fishcreator.hpp"
#include "vect2d.hpp"

#ifndef FOODCREATOR_H
#define FOODCREATOR_H

class Vegetale;

class FoodCreator : public FishCreator {
   public:
    /* parametri costruzione vegetale (posizione, valore nutrizionale NO LO FAREI DI DEFAULT ecc..) */
    Vegetale* createVegetale(const Vect2D& pos);
};

#endif