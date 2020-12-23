#include "deepptr.h"
#include "food.h"
// #include "quadtree.h"
#include "fish.h"
#include "vector.h"

#ifndef AQUARIUS_H
#define AQUARIUS_H

class Aquarius {
   private:
    Vector<DeepPtr<Fish>> fishes;
    Vector<DeepPtr<Food>> food;

   public:
    Aquarius();
    Aquarius(const Aquarius&);

    void addFish(Fish*);
    void addFood(Food*);

    const Vector<DeepPtr<Fish>>& getFishes(); // TODO const version
    const Vector<DeepPtr<Food>>& getFood();

    void update();
};

#endif