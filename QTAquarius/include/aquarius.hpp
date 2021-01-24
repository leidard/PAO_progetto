#include "deepptr.hpp"
#include "organismo.hpp"
#include "vector.hpp"

#ifndef AQUARIUS_H
#define AQUARIUS_H

class Aquarius {
   private:
    const std::string _name;
    unsigned int _width, _height;
    Vector<DeepPtr<Organismo>> organismi;
    bool _autorespawn;

   public:
    static const int ORGANISM_LIMIT;
    Aquarius(const std::string& = "Unnamed Aquarius", unsigned int = 0, unsigned int = 0);

    const std::string& getName() const { return _name; }

    unsigned int getWidth() const;
    unsigned int getHeight() const;
    Vect2D getBounds() const;

    void setSize(unsigned int, unsigned int);

    bool isAutoRespawnEnabled() const { return _autorespawn; } 
    void enableAutoRespawn() { _autorespawn = true; }
    void disableAutoRespawn() { _autorespawn = false; }

    void addOrganismo(Organismo*);
    bool canAddOrganismo() const;

    Vector<DeepPtr<Organismo>>& getAllOrganismi();

    void advance();
};

#endif
