#ifndef DAYCYCLE_H
#define DAYCYCLE_H

class DayCycle {
private:
    unsigned int awakeTime;
    unsigned int asleepTime;
    unsigned int progress;

public:
    explicit DayCycle(unsigned int = 0, unsigned int = 0);
    DayCycle(const DayCycle&);

    // getters
    int getDayTime() const;
    int getNightTime() const;
    int getProgress() const;
    bool isDay() const;
    bool isNight() const;

    // increment
    DayCycle& operator++();
    DayCycle operator++(int);
    DayCycle& operator+=(int);
};

#endif
