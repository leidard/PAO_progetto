
#ifndef STAMINA_H
#define STAMINA_H

class Stamina {
    friend bool operator<(double, const Stamina&);
    friend bool operator>(double, const Stamina&);
    friend bool operator<=(double, const Stamina&);
    friend bool operator>=(double, const Stamina&);
    friend bool operator==(double, const Stamina&);
    friend bool operator!=(double, const Stamina&);

   private:
    int _val;
    unsigned int _maxval;

   public:
    explicit Stamina(int = 0, unsigned int = 0);

    unsigned int getMax() const;
    int getVal() const;
    double getPercentage() const;
    void setMax(unsigned int);
    void setVal(int);
    Stamina& add(int);
    Stamina& rem(int);
    Stamina add(int) const;
    Stamina rem(int) const;

    Stamina& operator+=(int);
    Stamina& operator-=(int);
    Stamina operator+(int) const;
    Stamina operator-(int) const;

    operator double() const;  // ????

    bool operator<(const Stamina&) const;
    bool operator>(const Stamina&) const;
    bool operator<=(const Stamina&) const;
    bool operator>=(const Stamina&) const;
    bool operator==(const Stamina&) const;
    bool operator!=(const Stamina&) const;
};

#endif