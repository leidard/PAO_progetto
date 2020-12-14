
class Circle : public Range {
   private:
    Vect radius;

   public:
    Circle(const Vect& center_point, double r) : Range(center_point), radius(r, r) {}
    Vect getRadius() const { return radius; }
    bool contains(const Vect& v) const override {
        return center.distance(v) <= radius.getX();  // or getY() is the same
    }
    bool intersects(const Range& dr) const override {
        if (dynamic_cast<const Rectangle*>(&dr)) {
            const Rectangle& rect = dynamic_cast<const Rectangle&>(dr);

            double Xn = std::max(rect.center.getX() + rect.getHalfW().getX(), std::min(center.getX(), rect.center.getX() + rect.getHalfW().getX()));
            double Yn = std::max(rect.center.getY() + rect.getHalfH().getY(), std::min(center.getY(), rect.center.getY() + rect.getHalfH().getY()));

            Vect nearestPoint(Xn, Yn);

            return nearestPoint.distance(center) <= radius.getX();

        } else if (dynamic_cast<const Circle*>(&dr)) {
            const Circle& circ = dynamic_cast<const Circle&>(dr);
            return center.distance(circ.center) < radius.getX() + circ.radius.getX();
        } else
            return false;
    }
};