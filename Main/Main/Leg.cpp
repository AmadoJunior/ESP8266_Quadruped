#include <Arduino.h>
#include "Adafruit_PWMServoDriver.h"
#include "Leg.h"
#include <math.h>

//PULSE WIDTH =========================================================================
#define MIN_PULSE_WIDTH 575
#define MAX_PULSE_WIDTH 2400
#define FREQUENCY 50

Leg::Leg(){
    pwm = Adafruit_PWMServoDriver(0x40);
    coxaLenMm = 27;
    femurLenMm = 55;
    tibiaLenMm = 80;
    prevCoxaAngle = -1;
    prevFemurAngle = -1;
    prevTibiaAngle = -1;
}

Leg::Leg(int legNum, int coxaPin, int femurPin, int tibiaPin) : legNum(legNum), coxaPin(coxaPin), femurPin(femurPin), tibiaPin(tibiaPin) {
    pwm = Adafruit_PWMServoDriver(0x40);
    coxaLenMm = 27;
    femurLenMm = 55;
    tibiaLenMm = 80;
}
void Leg::setAngles(double x, double y, double z){
    
    //Finding Hypothenuse and Angle of Coxa ==========================
    double w = sqrt(pow(x, 2) + pow(y, 2));
    double coxaAngleR = atan2(y,x);
    //Rec Prev
    prevCoxaAngle = coxaAngle;
    coxaAngle = coxaAngleR * 57296 / 1000;

    //SETTING COXA ==================================================
    //Left Side Legs
    if(legNum  == 1){
      
      //Leg One 
        if(y < 0 && x < 0){
          //3rd Quadrant -> -90 to -180
          coxaAngle = 180 + coxaAngle;
          coxaAngle = 90 + coxaAngle;
        } else if(y >= 0 && x < 0){
          //2nd Quadrant -> 90 -> 180
          coxaAngle = coxaAngle - 90;
        }
        Serial.println("Calculated Angle for Leg 1");
        Serial.println(coxaAngle);

    } else if(legNum == 2){
      
      //Leg Two
      if(y < 0 && x < 0){
        //3rd Quadrant -> -90 to -180
        coxaAngle = 180 + coxaAngle;
        coxaAngle = 90 + coxaAngle;

      } else if(y >= 0 && x < 0){
        //2nd Quadrant -> 90 -> 180
        coxaAngle = coxaAngle - 90;

      }
      Serial.println("Calculated Angle for Leg 2");
      Serial.println(coxaAngle);
      
    } else if(legNum == 3){
      
      //Leg Three
      if(y >= 0 && x >= 0){
        //1rd Quadrant 0 -> 90
        coxaAngle = 90 + coxaAngle;
      } else if(y < 0){
        //4nd Quadrant -0 -> -90
        coxaAngle = 90 + coxaAngle;
      }
      Serial.println("Calculated Angle for Leg 3");
      Serial.println(coxaAngle);
      
    } else if(legNum == 4){
      
      //Leg Four
      if(y >= 0){
        //1rd Quadrant 0 -> 90
        coxaAngle = 90 + coxaAngle;
      } else if(y < 0){
        //4nd Quadrant -0 -> -90
        coxaAngle = 90 + coxaAngle;
      }
      Serial.println("Calculated Angle for Leg 4");
      Serial.println(coxaAngle);
      
    }

    //Finding Angle of Femur & Tibia ===================================
    
    //Calculating Distance
    double newX = w - coxaLenMm;

    //Calculating Tibia &  Femur Angle
      //Finding Distance from Point
      double hyp = sqrt(pow(newX, 2) + pow(z, 2));
      Serial.println("");
      Serial.println("Hypothenus");
      Serial.println(hyp);
    
      //Alpha
      double alpha = pow(femurLenMm, 2) + pow(tibiaLenMm, 2) - pow(newX, 2) - pow(z, 2);
      alpha = alpha / (2 * femurLenMm * tibiaLenMm);
      alpha = acos(alpha);
      alpha = (alpha / PI) * 180;
      Serial.println("");
      Serial.println("Alpha");
      Serial.println(alpha);
    
      //Q2
      double q2 = 180 - alpha;
      Serial.println("");
      Serial.println("Q2");
      Serial.println(q2);
    
      //Beta
      q2 = q2 * PI/180;
      double beta = tibiaLenMm * sin(q2);
      beta = beta / (femurLenMm + tibiaLenMm * cos(q2));
      beta = atan(beta);
      beta = (beta / PI) * 180;
      Serial.println("");
      Serial.println("Beta");
      Serial.println(beta);
    
      //Gamma
      double gamma = atan(z/newX);
      gamma = (gamma / PI) * 180;
      Serial.println("");
      Serial.println("Gamma");
      Serial.println(gamma);
    
      //Q1
      double q1 = gamma + beta;
      q2 = q2 * 180/PI;

    //Setting Tibia & Femur ===========================================

      if(legNum == 1){
        if(q1 >= 0){
          //1st Quadrant
          prevFemurAngle = femurAngle;
          prevTibiaAngle = tibiaAngle;
          femurAngle = 90 + q1;
          tibiaAngle = q2;
        }else if(q1 < 0) {
          //4th Quadrant
          prevFemurAngle = femurAngle;
          prevTibiaAngle = tibiaAngle;
          femurAngle = 90 + q1;
          tibiaAngle = q2;
        }
      } else if(legNum == 2){
        if(q1 >= 0){
          //1st Quadrant
          prevFemurAngle = femurAngle;
          prevTibiaAngle = tibiaAngle;
          femurAngle = 90 - q1;
          tibiaAngle = 180 - q2;
        }else if(q1 < 0) {
          //4th Quadrant
          prevFemurAngle = femurAngle;
          prevTibiaAngle = tibiaAngle;
          femurAngle = 90 - q1;
          tibiaAngle = 180 - q2;
        }
      } else if(legNum == 3){
       if(q1 >= 0){
          //1st Quadrant
          prevFemurAngle = femurAngle;
          prevTibiaAngle = tibiaAngle;
          femurAngle = 90 - q1;
          tibiaAngle = 180 - q2;
        }else if(q1 < 0) {
          //4th Quadrant
          prevFemurAngle = femurAngle;
          prevTibiaAngle = tibiaAngle;
          femurAngle = 90 - q1;
          tibiaAngle = 180 - q2;
        }
      } else if(legNum == 4){
        if(q1 >= 0){
          //1st Quadrant
          prevFemurAngle = femurAngle;
          prevTibiaAngle = tibiaAngle;
          femurAngle = 90 + q1;
          tibiaAngle = q2;
        }else if(q1 < 0) {
          //4th Quadrant
          prevFemurAngle = femurAngle;
          prevTibiaAngle = tibiaAngle;
          femurAngle = 90 + q1;
          tibiaAngle = q2;
        }
      }

}

int returnPulseWidth(double angle){
    int pulse_wide, analog_value;
    pulse_wide = map((int) angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
    analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
    return analog_value;
}

void Leg::updatePos(){
    if(legNum == 1){

        if(prevFemurAngle > coxaAngle){
            for(int i = prevCoxaAngle; i > coxaAngle; i--){
                pwm.setPWM(0, 0, returnPulseWidth(i));
                delay(10);
            }
        } else {
            for(int i = prevCoxaAngle; i < coxaAngle; i++){
                pwm.setPWM(0, 0, returnPulseWidth(i));
                delay(10);
            }
        }
        if(prevFemurAngle > femurAngle){
            for(int i = prevFemurAngle; i > femurAngle; i--){
                pwm.setPWM(1, 0, returnPulseWidth(i));
                delay(10);
            }
        } else {
            for(int i = prevFemurAngle; i < femurAngle; i++){
                pwm.setPWM(1, 0, returnPulseWidth(i));
                delay(10);
            }
        }
        if(prevTibiaAngle > tibiaAngle){
            for(int i = prevTibiaAngle; i > tibiaAngle; i--){
                pwm.setPWM(2, 0, returnPulseWidth(i));
                delay(10);
            }
        } else {
            for(int i = prevTibiaAngle; i < tibiaAngle; i++){
                pwm.setPWM(2, 0, returnPulseWidth(i));
                delay(10);
            }
        }
        
    } else if(legNum == 2){
        if(prevFemurAngle > coxaAngle){
            for(int i = prevCoxaAngle; i > coxaAngle; i--){
                pwm.setPWM(3, 0, returnPulseWidth(i));
                delay(10);
            }
        } else {
            for(int i = prevCoxaAngle; i < coxaAngle; i++){
                pwm.setPWM(3, 0, returnPulseWidth(i));
                delay(10);
            }
        }
        if(prevFemurAngle > femurAngle){
            for(int i = prevFemurAngle; i > femurAngle; i--){
                pwm.setPWM(4, 0, returnPulseWidth(i));
                delay(10);
            }
        } else {
            for(int i = prevFemurAngle; i < femurAngle; i++){
                pwm.setPWM(4, 0, returnPulseWidth(i));
                delay(10);
            }
        }
        if(prevTibiaAngle > tibiaAngle){
            for(int i = prevTibiaAngle; i > tibiaAngle; i--){
                pwm.setPWM(5, 0, returnPulseWidth(i));
                delay(10);
            }
        } else {
            for(int i = prevTibiaAngle; i < tibiaAngle; i++){
                pwm.setPWM(5, 0, returnPulseWidth(i));
                delay(10);
            }
        }
    } else if(legNum == 3){
        if(prevFemurAngle > coxaAngle){
            for(int i = prevCoxaAngle; i > coxaAngle; i--){
                pwm.setPWM(6, 0, returnPulseWidth(i));
                delay(10);
            }
        } else {
            for(int i = prevCoxaAngle; i < coxaAngle; i++){
                pwm.setPWM(6, 0, returnPulseWidth(i));
                delay(10);
            }
        }
        if(prevFemurAngle > femurAngle){
            for(int i = prevFemurAngle; i > femurAngle; i--){
                pwm.setPWM(7, 0, returnPulseWidth(i));
                delay(10);
            }
        } else {
            for(int i = prevFemurAngle; i < femurAngle; i++){
                pwm.setPWM(7, 0, returnPulseWidth(i));
                delay(10);
            }
        }
        if(prevTibiaAngle > tibiaAngle){
            for(int i = prevTibiaAngle; i > tibiaAngle; i--){
                pwm.setPWM(8, 0, returnPulseWidth(i));
                delay(10);
            }
        } else {
            for(int i = prevTibiaAngle; i < tibiaAngle; i++){
                pwm.setPWM(8, 0, returnPulseWidth(i));
                delay(10);
            }
        }
    } else if(legNum == 4){
        if(prevFemurAngle > coxaAngle){
            for(int i = prevCoxaAngle; i > coxaAngle; i--){
                pwm.setPWM(9, 0, returnPulseWidth(i));
                delay(10);
            }
        } else {
            for(int i = prevCoxaAngle; i < coxaAngle; i++){
                pwm.setPWM(9, 0, returnPulseWidth(i));
                delay(10);
            }
        }
        if(prevFemurAngle > femurAngle){
            for(int i = prevFemurAngle; i > femurAngle; i--){
                pwm.setPWM(10, 0, returnPulseWidth(i));
                delay(10);
            }
        } else {
            for(int i = prevFemurAngle; i < femurAngle; i++){
                pwm.setPWM(10, 0, returnPulseWidth(i));
                delay(10);
            }
        }
        if(prevTibiaAngle > tibiaAngle){
            for(int i = prevTibiaAngle; i > tibiaAngle; i--){
                pwm.setPWM(11, 0, returnPulseWidth(i));
                delay(10);
            }
        } else {
            for(int i = prevTibiaAngle; i < tibiaAngle; i++){
                pwm.setPWM(11, 0, returnPulseWidth(i));
                delay(10);
            }
        }
    }
}

void Leg::init(){
    switch(legNum){
        case 1:
            setAngles(-60,60,-60);
            break;
        case 2:
            setAngles(-60,-60,-60);
            break;
        case 3:
            setAngles(60,60,-60);
            break;
        case 4:
            setAngles(60,-60,-60);
            break;
    }
    if(legNum == 1){
        pwm.setPWM(0, 0, returnPulseWidth(coxaAngle));
        pwm.setPWM(1, 0, returnPulseWidth(femurAngle));
        pwm.setPWM(2, 0, returnPulseWidth(tibiaAngle));
    } else if(legNum == 2){
        pwm.setPWM(3, 0, returnPulseWidth(coxaAngle));
        pwm.setPWM(4, 0, returnPulseWidth(femurAngle));
        pwm.setPWM(5, 0, returnPulseWidth(tibiaAngle));
    } else if(legNum == 3){
        pwm.setPWM(6, 0, returnPulseWidth(coxaAngle));
        pwm.setPWM(7, 0, returnPulseWidth(femurAngle));
        pwm.setPWM(8, 0, returnPulseWidth(tibiaAngle));        
    } else if(legNum == 4){
        pwm.setPWM(9, 0, returnPulseWidth(coxaAngle));
        pwm.setPWM(10, 0, returnPulseWidth(femurAngle));
        pwm.setPWM(11, 0, returnPulseWidth(tibiaAngle));
    }
}

void Leg::lift(){
    switch(legNum){
        case 1:
            pwm.setPWM(1, 0, returnPulseWidth(170));
            break;
        case 2:
            pwm.setPWM(4, 0, returnPulseWidth(10));
            break;
        case 3:
            pwm.setPWM(7, 0, returnPulseWidth(10));
            break;
        case 4:
            pwm.setPWM(10, 0, returnPulseWidth(170));
            break;
    }
}

void Leg::setCoxaAngle(double angle){

}

void Leg::setPins(int coxa, int femur, int tibia){
    coxaPin = coxa;
    femurPin = femur;
    tibiaPin = tibia;
}

void Leg::setLegNum(int leg){
    legNum = leg;
}
