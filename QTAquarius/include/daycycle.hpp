
#ifndef DAYCYCLE_H
#define DAYCYCLE_H

class DayCycle {
   private:
    unsigned int awakeTime;
    unsigned int asleepTime;
    unsigned int progress;

   public:
    DayCycle(unsigned int = 0, unsigned int = 0);
    int getDayTime() const;
    int getNightTime() const;
    int getProgress() const;

    bool isDay() const;
    bool isNight() const;

    DayCycle& operator++();
    DayCycle operator++(int);
    DayCycle& operator+=(int);
};

#endif