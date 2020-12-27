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
   public:
    static void init(unsigned int = 0, unsigned int = 0);
    static Aquarius* getInstance();

   private:
    static Aquarius* instance;
    Aquarius(unsigned int = 0, unsigned int = 0);

    Aquarius(Aquarius const&) = delete;
    void operator=(Aquarius const&) = delete;

    unsigned int _width, _height;

    Vector<DeepPtr<Fish>> fish;
    Vector<DeepPtr<Food>> food;
    Vector<DeepPtr<Vegetale>> vegetali;

   public:
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

    void remFish(Vector<DeepPtr<Fish>>::iterator);  // const is ok??? remember that throws index out of range ??
    void remFood(Vector<DeepPtr<Food>>::iterator);  // const is ok??? remember that throws index out of range ??
    void remVegetale(Vector<DeepPtr<Vegetale>>::iterator);

    const Vector<DeepPtr<Fish>>& getAllFish() const;  // TODO: non const version???
    const Vector<DeepPtr<Food>>& getAllFood() const;
    const Vector<DeepPtr<Food>>& getAllVegetale() const;

    void advance();
};

#endif