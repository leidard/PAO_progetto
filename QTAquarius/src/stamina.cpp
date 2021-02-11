#include "stamina.hpp"

Stamina::Stamina(double maxval) : _maxval(maxval), _val(maxval) {}
Stamina::Stamina(const Stamina& o) : _maxval(o._maxval), _val(o._maxval) {} // special beahviour different from standard

double Stamina::getMax() const { return _maxval; }
double Stamina::getVal() const { return _val; }

double Stamina::getPercentage() const { return _val / _maxval; }

Stamina& Stamina::add(double v) {
    if (_val + v > _maxval) _val = _maxval;
    else _val += v;

    return *this;
}

Stamina& Stamina::rem(double v) {
    if (_val - v < 0) _val = 0;
    else _val -= v;
    return *this;
}

Stamina& Stamina::operator+=(double v) { return this->add(v); }
Stamina& Stamina::operator-=(double v) { return this->rem(v); }

bool Stamina::operator<(double val) const { return getPercentage() < val; }
bool Stamina::operator>(double val) const { return getPercentage() > val; }
bool Stamina::operator<=(double val) const { return getPercentage() <= val; }
bool Stamina::operator>=(double val) const { return getPercentage() >= val; }
bool Stamina::operator==(double val) const { return getPercentage() == val; }
bool Stamina::operator!=(double val) const { return getPercentage() != val; }
