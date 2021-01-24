
#ifndef STAMINA_H
#define STAMINA_H

class Stamina {
   private:
    double _maxval;
    double _val;

   public:
    explicit Stamina(double);
    Stamina(const Stamina&);

    double getMax() const;
    double getVal() const;

    double getPercentage() const;

    void setValToMax();

    Stamina& add(double);
    Stamina& rem(double);

    Stamina& operator+=(double);
    Stamina& operator-=(double);

    bool operator<(double val) const;
    bool operator>(double val) const;
    bool operator<=(double val) const;
    bool operator>=(double val) const;
    bool operator==(double val) const;
    bool operator!=(double val) const;
};

#endif
