#include <circle.h>
#include <range.h>
#include <rectangle.h>

#include <vector>

class Quadtree {
   private:
    const static int DEPTH_LIMIT = 5;  // log4(n)
    /*
    256   <= 4
    1024  <= 5
    4096  <= 6
    16384 <= 7
    65536 <= 8
    */
    const static int CAPACITY = 4;
    Rectangle boundary;
    Quadtree* nw;  //northwest
    Quadtree* ne;  //northeast
    Quadtree* sw;  //southwest
    Quadtree* se;  //southeast
    std::vector<Vect> points;

    void _queryRange(const Range& range, std::vector<Vect>* pointsInRange) const;

   public:
    Quadtree();
    ~Quadtree();
    Quadtree(const Rectangle& boundary);

    void subdivide();
    bool insert(Vect x);
    void reset();
    std::vector<Vect> queryRange(const Range& range) const;
};