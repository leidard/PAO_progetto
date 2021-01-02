#include <utility>

#include "deepptr.hpp"
#include "fish.hpp"
#include "vector.hpp"

#ifndef AQUARIUS_H
#define AQUARIUS_H

typedef std::pair<unsigned int, unsigned int> aq_size;

class Aquarius {
   private:
    unsigned int _width, _height;

    Vector<DeepPtr<Fish>> fish;

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

    void addFish(Fish*);

    void remFish(Vector<DeepPtr<Fish>>::iterator);

    Vector<DeepPtr<Fish>>& getAllFish();  // TODO: non const version???

    void advance();
};

#endif
