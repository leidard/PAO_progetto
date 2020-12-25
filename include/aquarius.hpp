#include "deepptr.hpp"
#include "food.hpp"
// #include "quadtree.hpp"
#include "fish.hpp"
#include "vector.hpp"

#ifndef AQUARIUS_H
#define AQUARIUS_H


//potrebbe servire model???

class Aquarius {
   private:
    Vector<DeepPtr<Fish>> fishes;
    Vector<DeepPtr<Food>> food;

   public:
    void addFish(Fish*);
    void addFood(Food*);

    const Fish* remFish(unsigned int);  // const is ok??? throws index out of range
    const Food* remFood(unsigned int);  // const is ok??? throws index out of range

    Fish& getFish(unsigned int);
    Food& getFood(unsigned int);
    const Fish& getFish(unsigned int) const;
    const Food& getFood(unsigned int) const;

    const Vector<DeepPtr<Fish>>& getFishes();  // TODO const version
    const Vector<DeepPtr<Food>>& getFood();

    void update();
};

#endif