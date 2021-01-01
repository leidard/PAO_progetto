#include <utility>

#include "deepptr.hpp"
#include "fish.hpp"
#include "food.hpp"
#include "vector.hpp"
#include "vegetale.hpp"

#ifndef AQUARIUS_H
#define AQUARIUS_H

typedef std::pair<unsigned int, unsigned int> aq_size;

class Aquarius {
   private:
    unsigned int _width, _height;

    Vector<DeepPtr<Fish>> fish;
    Vector<DeepPtr<Food>> food;
    Vector<DeepPtr<Vegetale>> vegetali;

   public:
    Aquarius(unsigned int = 0, unsigned int = 0);

    unsigned int getWidth() const;
    unsigned int getHeight() const;
    aq_size getSize() const;

    void setWidth(unsigned int);
    void setHeight(unsigned int);
    void setSize(unsigned int, unsigned int);
    void setSize(const aq_size&);
    void setSize(const Vect2D&);

    Fish& getFish(unsigned int);
    Food& getFood(unsigned int);
    Vegetale& getVegetale(unsigned int);

    const Fish& getFish(unsigned int) const;
    const Food& getFood(unsigned int) const;
    const Vegetale& getVegetale(unsigned int) const;

    void addFish(Fish*);
    void addFood(Food*);
    void addVegetale(Vegetale*);

    void remFish(Vector<DeepPtr<Fish>>::iterator);
    void remFood(Vector<DeepPtr<Food>>::iterator);

    Vector<DeepPtr<Fish>>& getAllFish();  // TODO: non const version???
    Vector<DeepPtr<Food>>& getAllFood();
    Vector<DeepPtr<Vegetale>>& getAllVegetale();

    void advance();
};

#endif
