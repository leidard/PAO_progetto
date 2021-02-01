#include "deepptr.hpp"
#include "organismo.hpp"
#include "vector.hpp"

#ifndef AQUARIUS_H
#define AQUARIUS_H

class Aquarius {
   private:
    std::string _name;
    unsigned int _width, _height;
    Vector<DeepPtr<Organismo>> organismi;
    bool _autorespawn;

   public:
    static const int ORGANISM_LIMIT;
    Aquarius(const std::string& = "Unnamed Aquarius", unsigned int = 0, unsigned int = 0);

    void setName(const std::string& name) ;
    const std::string& getName() const ;

    unsigned int getWidth() const;
    unsigned int getHeight() const;
    Vect2D getBounds() const;

    void setSize(unsigned int, unsigned int);


    bool isAutoRespawnEnabled() const;
    void enableAutoRespawn() ;
    void disableAutoRespawn() ;

    void addOrganismo(Organismo*);
    bool canAddOrganismo() const;

    Vector<DeepPtr<Organismo>>& getAllOrganismi();

    void advance();
};

#endif
