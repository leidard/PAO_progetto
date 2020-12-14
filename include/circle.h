#include <range.h>
#include <vect.h>

class Circle : public Range {
   private:
    Vect radius;

   public:
    Circle(const Vect& center_point, double r) : Range(center_point), radius(r, r) {}
    Vect getRadius() const;
    bool contains(const Vect& v) const override;
    bool intersects(const Range& dr) const override;
};