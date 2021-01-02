
#include <map>
#include <tuple>
#include <vector>

#include "vect2d.hpp"

class Range {
   private:
    double _x, _y, _w, _h;
    Vect2D topleft() const {
        return Vect2D(_x, _y);
    }
    Vect2D topright() const {
        return Vect2D(_x + _w, _y);
    }
    Vect2D bottomleft() const {
        return Vect2D(_x, _y + _h);
    }
    Vect2D bottomright() const {
        return Vect2D(_x + _w, _y + _h);
    }

   public:
    Range(double w, double h) : _x(0), _y(0), _w(w), _h(h) {}
    Range(double x, double y, double w, double h) : _x(x), _y(y), _w(w), _h(h) {}
    Range(const Range&) = default;
    std::tuple<Range, Range, Range, Range> divide() const {
        return std::tuple<Range, Range, Range, Range>(
            Range(_x, _y, _w / 2, _h / 2),                     // nw
            Range(_x + _w / 2, _y, _w / 2, _h / 2),            // ne
            Range(_x, _y + _h / 2, _w / 2, _h / 2),            // sw
            Range(_x + _w / 2, _y + _h / 2, _w / 2, _h / 2));  // se
    }
    bool contains(const Vect2D& point) const {
        auto tl = topleft();
        auto br = Vect2D(_x + _w, _y + _h);
        ;
        auto c1 = point >= topleft();
        auto c2 = point <= bottomright();
        tl + br;
        c1&& c2;

        return point >= topleft() && point <= bottomright();
    }
    bool intersects(const Range& range) const {
        return topleft() <= range.bottomright() && bottomright() > range.topleft();
    }
};

template <class T>
class BSPTree {
   private:
    Range _range;
    const unsigned int CAPACITY = 10;
    std::vector<std::pair<Vect2D, T*>> _data;
    BSPTree* nw;
    BSPTree* ne;
    BSPTree* sw;
    BSPTree* se;

   public:
    BSPTree(const Range& range) : _range(range), _data(), nw(nullptr), ne(nullptr), sw(nullptr), se(nullptr) {}

    /*
        Pass the position of the element and the Reference that will be stored in a DeepPtr
    */
    bool insert(const Vect2D& position, T* data) {
        if (!_range.contains(position)) return false;

        if (_data.size() < CAPACITY) {
            _data.push_back(std::pair<Vect2D, T*>(position, data));
            return true;
        }

        if (nw == nullptr) {
            auto ranges = _range.divide();
            nw = new BSPTree(std::get<0>(ranges));
            ne = new BSPTree(std::get<1>(ranges));
            sw = new BSPTree(std::get<2>(ranges));
            se = new BSPTree(std::get<3>(ranges));
        }

        // the first one that accept it it will retur true and exit from the or, preventing double insert;
        return nw->insert(position, data) || ne->insert(position, data) || sw->insert(position, data) || se->insert(position, data);
    }

    T* click(double x, double y, double halfsize) {
        return click(Range(x - halfsize, y -halfsize, halfsize * 2, halfsize * 2));
    }

    T* click(const Vect2D& position, double halfsize) {
        return click(Range(position.x() - halfsize, position.y() - halfsize, halfsize * 2, halfsize * 2));
    }

    /* return the first element found in that range, be sure to keep it small enough*/
    T* click(const Range& r) {
        if (!_range.intersects(r)) return nullptr;

        for (const std::pair<Vect2D, T*>& i : _data) {
            if (r.contains(i.first)) return i.second;
        }

        if (nw == nullptr)
            return nullptr;

        // nullptr is automatically casted to bool so if it's != nullptr it means it has found something
        // otherwise if nw returns nullptr it goes to ne and etc... till it reaches se;
        if (T* ret = nw->click(r)) return ret;
        if (T* ret = ne->click(r)) return ret;
        if (T* ret = sw->click(r)) return ret;
        if (T* ret = se->click(r)) return ret;
        return nullptr;
    }

    /* get all elements found in that range */
    void queryRange(const Range& r, std::vector<T*>& v) {
        if (!_range.intersects(r)) return;

        for (const std::pair<Vect2D, T*>& i : _data)
            if (r.contains(i.first)) v.push_back(i.second);

        if (nw == nullptr) return;

        nw->queryRange(r);
        ne->queryRange(r);
        sw->queryRange(r);
        se->queryRange(r);
    }
};