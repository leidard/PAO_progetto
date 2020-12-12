Vector {
  private:
    double x, y;
  public:
    Vector(): x(0), y(0) {}; # comportamento di default???
    Vector(const & Vector v): x(v.x), y(v.y) {}; # non necessario, comportamento di default
    Vector(double xx, double yy) : x(xx), y(yy) {}; # comportamento di default ???

    double modulo() const;
    normalize(); # non const

    operator=(Vector);
    operator==(Vector) const;
    operator

    operator+(Vector) # sum
    operator+=(Vector)
    operator*(Vector) # dot product
    operator*=(Vector)
    operator*(float ) # scalar
    operator*=(float )
    
    # divisione
    # sottrazione
    # opeartore di negazione?? operator!
    
    // output operator
 }
