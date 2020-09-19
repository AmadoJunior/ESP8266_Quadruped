
#ifndef LEG_H
#define LEG_H
#include "Adafruit_PWMServoDriver.h"
#include "Coordinates.h"

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
        //Public Vars
        Adafruit_PWMServoDriver pwm;
        Coordinates curCoordinates;
        Coordinates desiredCoordinates;

        //Constructors and Mehods
        Leg();
        Leg(byte legNum, byte coxaPin, byte femurPin, byte tibiaPin);
        void setAngles(float x, float y, float z); 
        void updatePos();
        void lift();
        void setCoxaAngle(float angle);
        void moveLeg(float x, float y, float z, bool lift);
        static int returnPulseWidht(float angle);
        void init(); 
        void calibrate(float x, float y, float z);
        //Setters
        void setDesiredCoordinates(float x, float y, float z);
        void setPins(byte coxaPin, byte femurPin, byte tibiaPin);
        void setLegNum(byte legNum);
        bool setCurCoordinateX(float x);
        bool setCurCoordinateY(float y);
        bool setCurCoordinateZ(float z);
        //Getters
        
};

#endif