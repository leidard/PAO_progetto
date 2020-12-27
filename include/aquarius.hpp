#include <utility>

#include "deepptr.hpp"
#include "fish.hpp"
#include "food.hpp"
#include "vector.hpp"

#ifndef AQUARIUS_H
#define AQUARIUS_H

typedef std::pair<unsigned int, unsigned int> aq_size;

// potrebbe servire model???
// singleton
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

    Vector<DeepPtr<Fish>> fishes;
    Vector<DeepPtr<Food>> food;

   public:
    unsigned int getWidth() const;
    unsigned int getHeight() const;
    aq_size getSize() const;

    void setWidth(unsigned int);
    void setHeight(unsigned int);
    void setSize(const aq_size&);

    Fish& getFish(unsigned int);
    Food& getFood(unsigned int);

    void addFish(Fish*);
    void addFood(Food*);

    void remFish(Vector<DeepPtr<Fish>>::iterator);  // const is ok??? remember that throws index out of range
    void remFood(Vector<DeepPtr<Food>>::iterator);  // const is ok??? remember that throws index out of range

    const Fish& getFish(unsigned int) const;
    const Food& getFood(unsigned int) const;

    const Vector<DeepPtr<Fish>>& getFishes() const;  // TODO: non const version???
    const Vector<DeepPtr<Food>>& getFood() const;

    void reset();
    void load(/**/);

    void update();
};

#endif