#include "daycycle.h"

DayCycle::DayCycle(int day, int night) : dayTime(day), nightTime(nightTime) {}

int DayCycle::getDayTime() const { return dayTime; }
int DayCycle::getNightTime() const { return nightTime; }
int DayCycle::getProgress() const { return progress % (dayTime + nightTime); }
int DayCycle::getCycles() const { return progress / (dayTime + nightTime); }

void DayCycle::setDayTime(int day) { dayTime = day; }
void DayCycle::setNightTime(int night) { nightTime = night; }
void DayCycle::setProgress(int prog) { progress = prog % (dayTime + nightTime); }

DayCycle& DayCycle::operator++() {
    progress++;
    return *this;
}
DayCycle DayCycle::operator++(int) {
    DayCycle tmp(*this);
    progress++;
    tmp;
}
void DayCycle::operator+=(int increment) { progress += increment; }