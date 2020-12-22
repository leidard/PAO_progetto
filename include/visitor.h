#include "vect2d.h"

#ifndef VISITOR_H
#define VISITOR_H

class Circle;
class Slice;
class Rectangle;

class Visitor {
   public:
    virtual bool visit(const Circle&) const = 0;
    virtual bool visit(const Slice&) const = 0;
    virtual bool visit(const Rectangle&) const = 0;
};

#endif