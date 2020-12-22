
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

Stamina::Stamina(int val, unsigned int maxval) : _val(val), _maxval(maxval == 0 ? val : maxval) {}

unsigned int Stamina::getMax() const { return _maxval; }
int Stamina::getVal() const { return _val; }
double Stamina::getPercentage() const { return _val / (double)_maxval; }
void Stamina::setMax(unsigned int v) { _maxval = v; }
void Stamina::setVal(int v) { _val = v; }
Stamina& Stamina::add(int v) {
    _val += v;
    return *this;
}
Stamina& Stamina::rem(int v) {
    _val -= v;
    return *this;
}
Stamina Stamina::add(int v) const { return Stamina(_val + v, _maxval); }
Stamina Stamina::rem(int v) const { return Stamina(_val - v, _maxval); }

Stamina& Stamina::operator+=(int v) { return this->add(v); }
Stamina& Stamina::operator-=(int v) { return this->rem(v); }
Stamina Stamina::operator+(int v) const { return this->add(v); }
Stamina Stamina::operator-(int v) const { return this->rem(v); }

Stamina::operator double() const { return getPercentage(); }

bool Stamina::operator<(const Stamina& s) const { return getPercentage() < s.getPercentage(); }
bool Stamina::operator>(const Stamina& s) const { return getPercentage() > s.getPercentage(); }
bool Stamina::operator<=(const Stamina& s) const { return getPercentage() <= s.getPercentage(); }
bool Stamina::operator>=(const Stamina& s) const { return getPercentage() >= s.getPercentage(); }
bool Stamina::operator==(const Stamina& s) const { return getPercentage() == s.getPercentage(); }
bool Stamina::operator!=(const Stamina& s) const { return getPercentage() != s.getPercentage(); }