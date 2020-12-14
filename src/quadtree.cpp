#include <../include/range.h>
#include <../include/rectangle.h>
#include <../include/vect.h>

#include <cmath>
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

    void _queryRange(const Range& range, std::vector<Vect>* pointsInRange) const {
        if (!boundary.intersects(range))
            return;

        for (auto& i : points) {
            if (range.contains(i)) pointsInRange->push_back(i);
        }

        if (nw == nullptr)
            return;

        nw->_queryRange(range, pointsInRange);
        ne->_queryRange(range, pointsInRange);
        sw->_queryRange(range, pointsInRange);
        se->_queryRange(range, pointsInRange);
    }

   public:
    Quadtree();
    ~Quadtree() {
        delete nw;
        delete ne;
        delete sw;
        delete se;
    }
    Quadtree(const Rectangle& boundary) : boundary(boundary) {}
    Quadtree(const Rectangle& boundary) : boundary(boundary), points(std::vector<Vect>()){};

    void subdivide() {
        nw = new Quadtree(boundary.nw());
        ne = new Quadtree(boundary.ne());
        sw = new Quadtree(boundary.sw());
        se = new Quadtree(boundary.se());
    }

    bool insert(Vect x) {
        if (!boundary.contains(x))
            return false;

        if (points.size() < CAPACITY) {
            points.push_back(x);
            return true;
        }

        if (nw == nullptr)
            subdivide();

        return nw->insert(x) || ne->insert(x) || sw->insert(x) || se->insert(x);
    }

    void reset() {
        points.clear();
        delete nw;
        delete ne;
        delete sw;
        delete se;
    }

    std::vector<Vect> queryRange(const Range& range) const {
        std::vector<Vect> pointsInRange;
        _queryRange(range, &pointsInRange);
        return pointsInRange;
    }
};