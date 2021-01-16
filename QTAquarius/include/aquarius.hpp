#include "deepptr.hpp"
#include "organismo.hpp"
#include "vector.hpp"

#ifndef AQUARIUS_H
#define AQUARIUS_H

class Aquarius {
   private:
    unsigned int _width, _height;
    Vector<DeepPtr<Organismo>> organismi;

   public:
    static const int ORGANISM_LIMIT;
    Aquarius(unsigned int = 0, unsigned int = 0);

    unsigned int getWidth() const;
    unsigned int getHeight() const;

    void setSize(unsigned int, unsigned int);

    void addOrganismo(Organismo*);
    bool canAddOrganismo() const;

    Vector<DeepPtr<Organismo>>& getAllOrganismi();

    void advance();
};

#endif
