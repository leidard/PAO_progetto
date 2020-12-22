#include <vector>

#include "cella.h"
#include "fov.h"
#include "vect2d.h"

#ifndef QUADTREE_H
#define QUADTREE_H

class Quadtree {
   private:
    /*const static int DEPTH_LIMIT = 5;  // log4(n)
    
    256   <= 4
    1024  <= 5
    4096  <= 6
    16384 <= 7
    65536 <= 8
    */
    const static int CAPACITY;  //= 4;
    Cella boundary;
    Quadtree* nw;  //northwest
    Quadtree* ne;  //northeast
    Quadtree* sw;  //southwest
    Quadtree* se;  //southeast
    std::vector<Vect2D> points;

    void _queryRange(const FoV& range, std::vector<Vect2D>* pointsInRange) const;

   public:
    Quadtree();
    ~Quadtree();
    Quadtree(const Cella& boundary);

    void subdivide();
    bool insert(Vect2D);
    void reset();
    std::vector<Vect2D> queryRange(const FoV&) const;
};

#endif