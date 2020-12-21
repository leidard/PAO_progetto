#include <include/cella.h>
#include <include/fov.h>
#include <include/quadtree.h>
#include <include/vect.h>

#include <cmath>
#include <vector>

const static int Quadtree::CAPACITY = 4;

void Quadtree::_queryRange(const FoV& range, std::vector<Vect>* pointsInRange) const {
    if (!range.accept(boundary))
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

Quadtree::Quadtree() {}
Quadtree::~Quadtree() {
    delete nw;
    delete ne;
    delete sw;
    delete se;
}
Quadtree::Quadtree(const Cella& boundary) : boundary(boundary) {}
Quadtree::Quadtree(const Cella& boundary) : boundary(boundary), points(std::vector<Vect>()){};

void Quadtree::subdivide() {
    nw = new Quadtree(boundary.nw());
    ne = new Quadtree(boundary.ne());
    sw = new Quadtree(boundary.sw());
    se = new Quadtree(boundary.se());
}

bool Quadtree::insert(Vect x) {
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

void Quadtree::reset() {
    points.clear();
    delete nw;
    delete ne;
    delete sw;
    delete se;
}

std::vector<Vect> Quadtree::queryRange(const FoV& range) const {
    std::vector<Vect> pointsInRange;
    _queryRange(range, &pointsInRange);
    return pointsInRange;
}
