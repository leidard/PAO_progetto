class Range {
   private:
   public:
    Vect center;
    Range(const Vect& center_point) : center(center_point) {}
    virtual ~Range() = 0;
    virtual bool contains(const Vect& v) const = 0;
    virtual bool intersects(const Range& range) const = 0;
};