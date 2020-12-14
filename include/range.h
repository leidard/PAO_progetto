#ifndef RANGE_H
#define RANGE_H
class Range {
   private:
   public:
    Vect center;
    Range(const Vect& center_point);
    virtual ~Range() = 0;
    virtual bool contains(const Vect& v) const = 0;
};
#endif