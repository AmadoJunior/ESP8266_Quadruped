//Libraries =========================================================================
#include "Wire.h"
#include "Adafruit_PWMServoDriver.h"
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
#include <math.h>

//PULSE WIDTH =========================================================================
#define MIN_PULSE_WIDTH 575
#define MAX_PULSE_WIDTH 2400
#define FREQUENCY 50

//GLOBAL VARS =================================================================
//bool STATUS = false;

//METHODS ====================================================================
int returnPulseWidth(double angle){
  int pulse_wide, analog_value;
  pulse_wide = map((int) angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  return analog_value;
}


//CARTISIANTOPOLAR METHOD ============================================================
void cartesianToPolar(int legNum, double x, double y, double z){
  
  //Finding Hypothenuse and Angle of Coxa ==========================
    double w = sqrt(pow(x, 2) + pow(y, 2));
    double coxaAngleR = atan2(y,x);
    double coxaAngleD = coxaAngleR * 57296 / 1000;
    Serial.println("");
    Serial.println("Coxa Angle");
    Serial.println(coxaAngleD);
    
  //MOVING COXA ==================================================
    //Left Side Legs
    if(legNum  == 1){
      
      //Leg One 
        if(y < 0 && x < 0){
          //3rd Quadrant -> -90 to -180
          coxaAngleD = 180 + coxaAngleD;
          coxaAngleD = 90 + coxaAngleD;
          pwm.setPWM(0, 0, returnPulseWidth(coxaAngleD));
        } else if(y >= 0 && x < 0){
          //2nd Quadrant -> 90 -> 180
          coxaAngleD = coxaAngleD - 90;
          pwm.setPWM(0, 0, returnPulseWidth(coxaAngleD));
        }
        Serial.println("Calculated Angle for Leg 1");
        Serial.println(coxaAngleD);
        
    } else if(legNum == 2){
      
      //Leg Two
      if(y < 0 && x < 0){
        //3rd Quadrant -> -90 to -180
        coxaAngleD = 180 + coxaAngleD;
        coxaAngleD = 90 + coxaAngleD;
        pwm.setPWM(3, 0, returnPulseWidth(coxaAngleD));
      } else if(y >= 0 && x < 0){
        //2nd Quadrant -> 90 -> 180
        coxaAngleD = coxaAngleD - 90;
        pwm.setPWM(3, 0, returnPulseWidth(coxaAngleD));
      }
      Serial.println("Calculated Angle for Leg 2");
      Serial.println(coxaAngleD);
      
    } else if(legNum == 3){
      
      //Leg Three
      if(y >= 0 && x >= 0){
        //1rd Quadrant 0 -> 90
        coxaAngleD = 90 + coxaAngleD;
        pwm.setPWM(6, 0, returnPulseWidth(coxaAngleD));
      } else if(y < 0){
        //4nd Quadrant -0 -> -90
        coxaAngleD = 90 + coxaAngleD;
        pwm.setPWM(6, 0, returnPulseWidth(coxaAngleD));
      }
      Serial.println("Calculated Angle for Leg 3");
      Serial.println(coxaAngleD);
      
    } else if(legNum == 4){
      
      //Leg Four
      if(y >= 0){
        //1rd Quadrant 0 -> 90
        coxaAngleD = 90 + coxaAngleD;
        pwm.setPWM(9, 0, returnPulseWidth(coxaAngleD));
      } else if(y < 0){
        //4nd Quadrant -0 -> -90
        coxaAngleD = 90 + coxaAngleD;
        pwm.setPWM(9, 0, returnPulseWidth(coxaAngleD));
      }
      Serial.println("Calculated Angle for Leg 4");
      Serial.println(coxaAngleD);
      
    }
    
  //Finding Angle of Femur & Tibia ===================================
    //Init Vars
    double femurAngle;
    double tibiaAngle;
    
    //TO DO LEG MEASUREMENTS
    double coxaLenMm = 27;
    double femurLenMm = 55;
    double tibiaLenMm = 80;
    
    //Calculating Distance
    double newX = w - coxaLenMm;

    //Calculating Tibia &  Femur Angle
      //Finding Distance from Point
      double hyp = sqrt(pow(newX, 2) + pow(z, 2));
      //Serial.println("");
      //Serial.println("Hypothenus");
      //Serial.println(hyp);
    
      //Alpha
      double alpha = pow(femurLenMm, 2) + pow(tibiaLenMm, 2) - pow(newX, 2) - pow(z, 2);
      alpha = alpha / (2 * femurLenMm * tibiaLenMm);
      alpha = acos(alpha);
      alpha = (alpha / PI) * 180;
      //Serial.println("");
      //Serial.println("Alpha");
      //Serial.println(alpha);
    
      //Q2
      double q2 = 180 - alpha;
      //Serial.println("");
      //Serial.println("Q2");
      //Serial.println(q2);
    
      //Beta
      q2 = q2 * PI/180;
      double beta = tibiaLenMm * sin(q2);
      beta = beta / (femurLenMm + tibiaLenMm * cos(q2));
      beta = atan(beta);
      beta = (beta / PI) * 180;
      //Serial.println("");
      //Serial.println("Beta");
      //Serial.println(beta);
    
      //Gamma
      double gamma = atan(z/newX);
      gamma = (gamma / PI) * 180;
      //Serial.println("");
      //Serial.println("Gamma");
      //Serial.println(gamma);
    
      //Q1
      double q1 = gamma + beta;
      q2 = q2 * 180/PI;
      //Serial.println("");
      //Serial.println("Q1");
      //Serial.println(q1);

    //Testing =======================================================

    /*
    q1 -> 0 => 90 When in 1st Quadrant OR -1 => (-90) When in 4th Quadrant
    q2 -> Negative Value that rotates clockwise from the origin 
    */

    
    //Moving Tibia & Femur ===========================================

      if(legNum == 1){
        if(q1 >= 0){
          //1st Quadrant
          femurAngle = 90 + q1;
          tibiaAngle= q2;
          pwm.setPWM(1, 0, returnPulseWidth(femurAngle));
          pwm.setPWM(2, 0, returnPulseWidth(tibiaAngle));
        }else if(q1 < 0) {
          //4th Quadrant
          femurAngle = 90 + q1;
          tibiaAngle = q2;
          pwm.setPWM(1, 0, returnPulseWidth(femurAngle));
          pwm.setPWM(2, 0, returnPulseWidth(tibiaAngle));
        }
      } else if(legNum == 2){
        if(q1 >= 0){
          //1st Quadrant
          femurAngle = 90 - q1;
          tibiaAngle = 180 - q2;
          pwm.setPWM(4, 0, returnPulseWidth(femurAngle));
          delay(500);
          pwm.setPWM(5, 0, returnPulseWidth(tibiaAngle));
        }else if(q1 < 0) {
          //4th Quadrant
          femurAngle = 90 - q1;
          tibiaAngle = 180 - q2;
          pwm.setPWM(4, 0, returnPulseWidth(femurAngle));
          pwm.setPWM(5, 0, returnPulseWidth(tibiaAngle));
        }
      } else if(legNum == 3){
       if(q1 >= 0){
          //1st Quadrant
          femurAngle = 90 - q1;
          tibiaAngle = 180 - q2;
          pwm.setPWM(7, 0, returnPulseWidth(femurAngle));
          pwm.setPWM(8, 0, returnPulseWidth(tibiaAngle));
        }else if(q1 < 0) {
          //4th Quadrant
          femurAngle = 90 - q1;
          tibiaAngle = 180 - q2;
          pwm.setPWM(7, 0, returnPulseWidth(femurAngle));
          pwm.setPWM(8, 0, returnPulseWidth(tibiaAngle));
        }
      } else if(legNum == 4){
        if(q1 >= 0){
          //1st Quadrant
          femurAngle = 90 + q1;
          tibiaAngle= q2;
          pwm.setPWM(10, 0, returnPulseWidth(femurAngle));
          pwm.setPWM(11, 0, returnPulseWidth(tibiaAngle));
        }else if(q1 < 0) {
          //4th Quadrant
          femurAngle = 90 + q1;
          tibiaAngle = q2;
          pwm.setPWM(10, 0, returnPulseWidth(femurAngle));
          pwm.setPWM(11, 0, returnPulseWidth(tibiaAngle));
        }
      }
}

void standBy(float heightMm){
  float femurAndTibiaAngles;
  double tibiaLenMm = 90;
  //Looping through pins
    for(int i = 0;  i < 12; i++){
      if(i%3 == 0){
        //Coxa
        switch(i){
          case 0:
            pwm.setPWM(i, 0, returnPulseWidth(45));
            //delay(500);
            break;
          case 3:
            pwm.setPWM(i, 0, returnPulseWidth(135));
            //delay(500);
            break;
          case 6:
            pwm.setPWM(i, 0, returnPulseWidth(135));
           //delay(500);
            break;
          case 9:
            pwm.setPWM(i, 0, returnPulseWidth(45));
            //delay(500);
            break;
        }
      } else {
        switch(i){
          case 1:
            femurAndTibiaAngles = map(heightMm, 0, 60, 180, 0);
            pwm.setPWM(i, 0, returnPulseWidth(femurAndTibiaAngles));
            break;
          case 2:
            femurAndTibiaAngles = map(heightMm, 0, 60, 180, 0);
            pwm.setPWM(i, 0, returnPulseWidth(femurAndTibiaAngles));
            break;
          case 4:
            femurAndTibiaAngles = map(heightMm, 0, 60, 0, 180);
            pwm.setPWM(i, 0, returnPulseWidth(femurAndTibiaAngles));
            break;
          case 5:
            femurAndTibiaAngles = map(heightMm, 0, 60, 0, 180);
            pwm.setPWM(i, 0, returnPulseWidth(femurAndTibiaAngles));
            break;
          case 7:
            femurAndTibiaAngles = map(heightMm, 0, 60, 0, 180);
            pwm.setPWM(i, 0, returnPulseWidth(femurAndTibiaAngles));
            break;
          case 8:
            femurAndTibiaAngles = map(heightMm, 0, 60, 0, 180);
            pwm.setPWM(i, 0, returnPulseWidth(femurAndTibiaAngles));
            break;
         case 10:
            femurAndTibiaAngles = map(heightMm, 0, 60, 180, 0);
            pwm.setPWM(i, 0, returnPulseWidth(femurAndTibiaAngles));
            break;
         case 11:
            femurAndTibiaAngles = map(heightMm, 0, 60, 180, 0);
            pwm.setPWM(i, 0, returnPulseWidth(femurAndTibiaAngles));
            break;
        }
      }       
    }
}


//SETUP =========================================================================
void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);
  //standBy(20);
}


//LOOP =========================================================================
void loop() {
  cartesianToPolar(1, -100, 80, 40);
  cartesianToPolar(2, -100, -80, 40);
  cartesianToPolar(3, 100, 80, 40);
  cartesianToPolar(4, 100, -80, 40);
  //pwm.setPWM(3, 0, returnPulseWidth(90));
  delay(10000);
}
