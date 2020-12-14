class Rectangle : public Range {
   private:
    Vect halfw;  // w / 2
    Vect halfh;  // h / 2

   public:
    Rectangle(const Vect& center_point, int width, int height) : Range(center_point), halfw(width / 2, 0), halfh(0, height / 2) {}
    Rectangle(const Vect& center_point, const Vect& width, const Vect& height) : Range(center_point), halfw(width.getX() / 2, 0), halfh(0, height.getY() / 2) {}
    Rectangle(const Rectangle& r) : Range(r.center), halfw(r.halfw), halfh(r.halfh) {}
    Vect getHalfW() const { return halfw; }
    Vect getHalfH() const { return halfh; }
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
    bool intersects(const Range& dr) const override {
        if (dynamic_cast<const Rectangle*>(&dr)) {
            const Rectangle& rect = dynamic_cast<const Rectangle&>(dr);

            auto min1 = center - halfw - halfh;
            auto max1 = center + halfw + halfh;
            auto min2 = rect.center - rect.halfw - rect.halfh;
            auto max2 = rect.center + rect.halfw + rect.halfh;

            // the smaller coord of this has to be lteq the maximum coord of the other
            // the maximum coord of this has to be gt   the minimum coord of the other
            return min1 <= max2 &&
                   max1 > min2;
        } else if (dynamic_cast<const Circle*>(&dr)) {
            const Circle& circ = dynamic_cast<const Circle&>(dr);

            double Xn = std::max(center.getX() + halfw.getX(), std::min(circ.center.getX(), center.getX() + halfw.getX()));
            double Yn = std::max(center.getY() + halfh.getY(), std::min(circ.center.getY(), center.getY() + halfh.getY()));

            Vect nearestPoint(Xn, Yn);

            return nearestPoint.distance(center) <= circ.getRadius().getX();
        } else
            return false;
    }
};