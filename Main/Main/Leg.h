
#ifndef LEG_H
#define LEG_H
#include "Adafruit_PWMServoDriver.h"

class Leg{
    private:
        byte legNum;
        byte coxaPin;
        byte femurPin;
        byte tibiaPin;
        float coxaLenMm;
        float femurLenMm;
        float tibiaLenMm;
        float coxaAngle;
        float femurAngle;
        float tibiaAngle;
        float prevCoxaAngle;
        float prevFemurAngle;
        float prevTibiaAngle;
        float coxaOffset;
        float femurOffset;
        float tibiaOffset;
    public: 
        Adafruit_PWMServoDriver pwm;
        Leg();
        Leg(byte legNum, byte coxaPin, byte femurPin, byte tibiaPin);
        void setAngles(float x, float y, float z);
        void updatePos();
        void lift();
        void setCoxaAngle(float angle);
        int returnPulseWidht(float angle);
        void init();
        void calibrate(float x, float y, float z);
        //Setters
        void setPins(byte coxaPin, byte femurPin, byte tibiaPin);
        void setLegNum(byte legNum);
};

#endif