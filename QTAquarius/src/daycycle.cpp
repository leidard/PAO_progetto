#include "daycycle.hpp"

DayCycle::DayCycle(unsigned int day, unsigned int night, unsigned int prog) : awakeTime(day), asleepTime(night), progress(prog) {}

int DayCycle::getDayTime() const { return awakeTime; }
int DayCycle::getNightTime() const { return asleepTime; }
int DayCycle::getProgress() const { return progress % (awakeTime + asleepTime); }
int DayCycle::getCycles() const { return progress / (awakeTime + asleepTime); }

void DayCycle::setDayTime(int day) { awakeTime = day; }
void DayCycle::setNightTime(int night) { asleepTime = night; }
void DayCycle::setProgress(int prog) { progress = prog % (awakeTime + asleepTime); }

DayCycle& DayCycle::operator++() {
    progress++;
    return *this;
}
DayCycle DayCycle::operator++(int) {
    DayCycle tmp(*this);
    progress++;
    return tmp;
}
DayCycle& DayCycle::operator+=(int increment) {
    progress += increment;
    return *this;
}
