#include "stamina.hpp"

Stamina::Stamina(unsigned int maxval) : _maxval(maxval), _val(maxval) {}

unsigned int Stamina::getMax() const { return _maxval; }
int Stamina::getVal() const { return _val; }

double Stamina::getPercentage() const { return _val / (double)_maxval; }

Stamina& Stamina::add(int v) {
    _val += v;
    return *this;
}
Stamina& Stamina::rem(int v) {
    _val -= v;
    return *this;
}

Stamina& Stamina::operator+=(int v) { return this->add(v); }
Stamina& Stamina::operator-=(int v) { return this->rem(v); }

bool Stamina::operator<(double val) const { return getPercentage() < val; }
bool Stamina::operator>(double val) const { return getPercentage() > val; }
bool Stamina::operator<=(double val) const { return getPercentage() <= val; }
bool Stamina::operator>=(double val) const { return getPercentage() >= val; }
bool Stamina::operator==(double val) const { return getPercentage() == val; }
bool Stamina::operator!=(double val) const { return getPercentage() != val; }