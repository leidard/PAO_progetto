#include "rectangle.h"
#include "vect2d.h"
#include "visitor.h"

#ifndef CELLA_H
#define CELLA_H

class Cella : public Visitor, public Rectangle {
   public:
    Cella(){};
    Cella(const Rectangle& r){};

    bool visit(const Circle& circ) const override;
    bool visit(const Slice& s) const override;
    bool visit(const Rectangle& rect) const override;

    Cella nw() const;
    Cella ne() const;
    Cella sw() const;
    Cella se() const;
};

#endif