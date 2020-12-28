
#ifndef STAMINA_H
#define STAMINA_H

class Stamina {
   private:
    unsigned int _maxval;
    int _val;

   public:
    explicit Stamina(unsigned int);

    unsigned int getMax() const;
    int getVal() const;

    double getPercentage() const;

    Stamina& add(int);
    Stamina& rem(int);

    Stamina& operator+=(int);
    Stamina& operator-=(int);

    bool operator<(double val) const;
    bool operator>(double val) const;
    bool operator<=(double val) const;
    bool operator>=(double val) const;
    bool operator==(double val) const;
    bool operator!=(double val) const;
};

#endif