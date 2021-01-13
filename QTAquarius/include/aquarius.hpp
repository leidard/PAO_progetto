#include "deepptr.hpp"
#include "organismo.hpp"
#include "vector.hpp"

#ifndef AQUARIUS_H
#define AQUARIUS_H

class Aquarius {
   private:
    unsigned int _width, _height;

    Vector<DeepPtr<Organismo>> fish;

   public:
    Aquarius(unsigned int = 0, unsigned int = 0);

    unsigned int getWidth() const;
    unsigned int getHeight() const;

    void setWidth(unsigned int);
    void setHeight(unsigned int);
    void setSize(unsigned int, unsigned int);

    void addFish(Organismo*);

    Vector<DeepPtr<Organismo>>& getAllFish();

    void advance();
};

#endif
