#include <circle.h>
#include <rectangle.h>
#include <slice.h>
#include <vect.h>

#ifndef VISITOR_H
#define VISITOR_H

class Visitor {
   public:
    virtual bool visit(const Circle&) const = 0;
    virtual bool visit(const Slice&) const = 0;
    virtual bool visit(const Rectangle&) const = 0;
};

#endif