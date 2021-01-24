#include "daycycle.hpp"

DayCycle::DayCycle(unsigned int day, unsigned int night) : awakeTime(day), asleepTime(night), progress(0) {}
DayCycle::DayCycle(const DayCycle& o) : awakeTime(o.awakeTime), asleepTime(o.asleepTime), progress(0) {}

int DayCycle::getDayTime() const { return awakeTime; }
int DayCycle::getNightTime() const { return asleepTime; }
int DayCycle::getProgress() const { return progress; }
bool DayCycle::isDay() const { return progress < awakeTime; };
bool DayCycle::isNight() const { return progress > awakeTime; };

DayCycle& DayCycle::operator++() {
    progress++;
    progress %= awakeTime + asleepTime;
    return *this;
}
DayCycle DayCycle::operator++(int) {
    DayCycle aux(*this);
    progress++;
    progress %= awakeTime + asleepTime;
    return aux;
}
DayCycle& DayCycle::operator+=(int increment) {
    progress += increment;
    progress %= awakeTime + asleepTime;
    return *this;
}
