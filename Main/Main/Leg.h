#ifndef LEG_H
#define LEG_H

#include "Adafruit_PWMServoDriver.h"

class Leg{
    private:
        int legNum;
        int coxaPin;
        int femurPin;
        int tibiaPin;
        double coxaLenMm;
        double femurLenMm;
        double tibiaLenMm;
        double coxaAngle;
        double femurAngle;
        double tibiaAngle;
        double prevCoxaAngle;
        double prevFemurAngle;
        double prevTibiaAngle;
    public: 
        Adafruit_PWMServoDriver pwm;
        Leg();
        Leg(int legNum, int coxaPin, int femurPin, int tibiaPin);
        void setAngles(double x, double y, double z);
        void updatePos();
        void lift();
        void setCoxaAngle(double angle);
        int returnPulseWidht(double angle);
        void init();
        //Setters
        void setPins(int coxaPin, int femurPin, int tibiaPin);
        void setLegNum(int legNum);
};

#endif