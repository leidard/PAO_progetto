#include "daycycle.h"

DayCycle::DayCycle(int day, int night) : awakeTime(day), asleepTime(asleepTime) {}

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
    tmp;
}
DayCycle& DayCycle::operator+=(int increment) { progress += increment; }