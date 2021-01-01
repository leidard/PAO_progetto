#include "stamina.hpp"

Stamina::Stamina(double maxval) : _maxval(maxval), _val(maxval) {}

double Stamina::getMax() const { return _maxval; }
double Stamina::getVal() const { return _val; }

void Stamina::setValToMax() { _val=_maxval; }

double Stamina::getPercentage() const { return _val / _maxval; }

Stamina& Stamina::add(double v) {
    _val += v;
    return *this;
}
Stamina& Stamina::rem(double v) {
    _val -= v;
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
