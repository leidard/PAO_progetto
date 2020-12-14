#include <cmath>
#include <vector>

// math vector?????
class Vect {
    friend bool operator<(const Vect&, const Vect&);
    friend bool operator>(const Vect&, const Vect&);
    friend bool operator<=(const Vect&, const Vect&);
    friend bool operator>=(const Vect&, const Vect&);
    friend bool operator==(const Vect&, const Vect&);
    friend bool operator!=(const Vect&, const Vect&);

   private:
    double x, y;

   public:
    Vect(double coord_x, double coord_y) : x(coord_x), y(coord_y) {}
    Vect(const Vect& v) : x(v.x), y(v.y) {}
    double getX() const { return y; }
    double getY() const { return x; }
    Vect getXVect() const { return Vect(x, 0); }
    Vect getYVect() const { return Vect(0, y); }

    Vect& normalize() {
        this->operator/=(magnitude());  // *this /= magnitude()
        return *this;
    }

    Vect normal() const {
        return this->operator/(magnitude());  // *this / magnitude()
    }

    double magnitude() const {  // modulo
        return std::sqrt(x * x + y * y);
    }

    double distance(const Vect& v) const {
        return (*this - v).magnitude();
    }

    Vect operator+(const Vect& v) const {
        return Vect(x + v.x, y + v.y);
    }
    Vect operator-(const Vect& v) const {
        return Vect(x - v.x, y - v.y);
    }
    Vect operator*(const Vect& v) const {
        return Vect(x * v.x, y * v.y);
    }
    Vect operator*(double n) const {
        return Vect(x * n, y * n);
    }
    Vect operator/(const Vect& v) const {
        return Vect(x / v.x, y / v.y);
    }
    Vect operator/(double n) const {  // can't divide by zero obv
        return Vect(x / n, y / n);
    }

    Vect& operator+=(const Vect& v) {
        x += v.x;
        y += v.y;
        return *this;
    }
    Vect& operator-=(const Vect& v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }
    Vect& operator*=(const Vect& v) {
        x *= v.x;
        y *= v.y;
        return *this;
    }
    Vect& operator*=(double n) {
        x *= n;
        y *= n;
        return *this;
    }
    Vect& operator/=(const Vect& v) {
        x /= v.x;
        y /= v.y;
        return *this;
    }
    Vect& operator/=(double n) {
        x /= n;
        y /= n;
        return *this;
    }
};

bool operator>(const Vect& v1, const Vect& v2) {
    return v1.x > v2.x && v1.y > v2.y;
}
bool operator>=(const Vect& v1, const Vect& v2) {
    return v1.x >= v2.x && v1.y >= v2.y;
}
bool operator<(const Vect& v1, const Vect& v2) {
    return v1.x < v2.x && v1.y < v2.y;
}
bool operator<=(const Vect& v1, const Vect& v2) {
    return v1.x <= v2.x && v1.y <= v2.y;
}
bool operator==(const Vect& v1, const Vect& v2) {
    return v1.x == v2.x && v1.y == v2.y;
}
bool operator!=(const Vect& v1, const Vect& v2) {
    return v1.x != v2.x || v1.y != v2.y;
}

class Quadtree {
   private:
    class DetectionRange {
       private:
       public:
        Vect center;
        DetectionRange(const Vect& center_point) : center(center_point) {}
        virtual ~DetectionRange() = 0;
        virtual bool contains(const Vect& v) const = 0;
        virtual bool intersects(const Rectangle& range) const = 0;
    };
    class Rectangle : public DetectionRange {
       private:
        Vect halfw;  // w / 2
        Vect halfh;  // h / 2

       public:
        Rectangle(const Vect& center_point, int width, int height) : DetectionRange(center_point), halfw(width / 2, 0), halfh(0, height / 2) {}
        Rectangle(const Vect& center_point, const Vect& width, const Vect& height) : DetectionRange(center_point), halfw(width.getX() / 2, 0), halfh(0, height.getY() / 2) {}
        Rectangle(const Rectangle& r) : DetectionRange(r.center), halfw(r.halfw), halfh(r.halfh) {}
        Rectangle nw() const {
            return Rectangle(center - halfw - halfh, halfw, halfh);
        }
        Rectangle ne() const {
            return Rectangle(center + halfw - halfh, halfw, halfh);
        }
        Rectangle sw() const {
            return Rectangle(center - halfw + halfh, halfw, halfh);
        }
        Rectangle se() const {
            return Rectangle(center + halfw + halfh, halfw, halfh);
        }
        bool contains(const Vect& v) const override {
            auto halfsize = halfw + halfh;
            auto bottomleft = center - halfsize;
            auto topright = center + halfsize;
            return v >= bottomleft && v <= topright;
        }
        bool intersects(const DetectionRange* r) const override {
            const Rectangle* range = dynamic_cast<const Rectangle*>(r);
            if (range == nullptr) return false;
            return !(
                range->center.getXVect() - range->halfw > center.getXVect() + halfw ||
                range->center.getXVect() + range->halfw > center.getXVect() - halfw ||
                range->center.getYVect() - range->halfh > center.getYVect() + halfh ||
                range->center.getYVect() + range->halfh > center.getYVect() - halfh);
        }
    };
    class Circle : public DetectionRange {
       private:
        double radius;

       public:
        Circle(const Vect& center_point, double r) : DetectionRange(center_point), radius(r) {}
        bool contains(const Vect& v) const override {
            auto m = (v - center).magnitude();
            return m <= radius;
        }
        bool intersects(const DetectionRange* r) const override {
            const Circle* rr = dynamic_cast<const Circle*>(r);
            if (rr == nullptr) return false;
            auto range = *r;

            Vect distanceXY = range.center - center;

            // radius of the circle
            let r = this.r;

            let w = range.w;
            let h = range.h;

            let edges = Math.pow((xDist - w), 2) + Math.pow((yDist - h), 2);

            // no intersection
            if (xDist > (r + w) || yDist > (r + h))
                return false;

            // intersection within the circle
            if (xDist <= w || yDist <= h)
                return true;

            // intersection on the edge of the circle
            return edges <= this.rSquared;
        }
    };
    static bool intersects(const Circle& c, const Rectangle& r);
    static bool intersects(const Rectangle& r, const Circle& c) { return Quadtree::intersects(c, r); }

    static bool intersects(const Circle& c1, const Circle& c2);
    static bool intersects(const Rectangle& r1, const Rectangle& r2);
    static bool intersects(const Rectangle& r, const DetectionRange* dr) {
        if (auto t = dynamic_cast<const Rectangle*>(dr))
            return Quadtree::intersects(r, *t);
        else if (auto t = dynamic_cast<const Circle*>(dr))
            return Quadtree::intersects(r, *t);
        else
            return false;
    }

    const static int DEPTH_LIMIT = 5;  // log4(n)
    const static int CAPACITY = 4;
    Rectangle boundary;
    Quadtree* nw;  //northwest
    Quadtree* ne;  //northeast
    Quadtree* sw;  //southwest
    Quadtree* se;  //southeast
    std::vector<Vect> points;

    void _queryRange(const Rectangle& range, std::vector<Vect>* pointsInRange) const {
        if (!Quadtree::intersects(boundary, &range))
            return;

        for (std::vector<Vect>::const_iterator i = points.begin(); i < points.end(); i++) {
            if (range.contains(*i))
                pointsInRange->push_back(*i);
        }

        if (nw == nullptr)
            return;

        nw->_queryRange(range, pointsInRange);
        ne->_queryRange(range, pointsInRange);
        sw->_queryRange(range, pointsInRange);
        se->_queryRange(range, pointsInRange);
    }

    void _queryRange(const Rectangle& range, std::vector<Vect>* pointsInRange) const {
        if (!Quadtree::intersects(boundary, &range))
            return;

        for (std::vector<Vect>::const_iterator i = points.begin(); i < points.end(); i++) {
            if (range.contains(*i))
                pointsInRange->push_back(*i);
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

    std::vector<Vect> queryRange(const Circle& range) const {
        std::vector<Vect> pointsInRange;
        _queryRange(range, &pointsInRange);
        return pointsInRange;
    }

    std::vector<Vect> queryRange(const Rectangle& range) const {
        std::vector<Vect> pointsInRange;
        _queryRange(range, &pointsInRange);
        return pointsInRange;
    }
};