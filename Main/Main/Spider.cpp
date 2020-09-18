#include "Spider.h"

Spider::Spider(int n){
    frequency = 50;

    //Populating legArray ===========================
      int count = 0;
      for(int i = 0; i < 12; i+=3){
        legArray[count].setPins(i, i+1, i+2);
        legArray[count].setLegNum(count+1);
        count++;
      }
}

void Spider::initPwm(){
    for(int i = 0; i < 4; i++){
        legArray[i].pwm.begin();
        legArray[i].pwm.setPWMFreq(frequency);
        legArray[i].init();
        delay(1000);
    }
    delay(1000);
}

void Spider::initCalibration(){
  //Calibration =====================
      /*
      Expected:  
                x: 100, y: 80, z: 45
      */
      float actualCoordinates[4][3] = {
        {-95,85,45},
        {-110,-74,55},
        {92.5,97.5,45},
        {108,-92,33}
      };
      for(int i = 0; i < 4; i++){
          legArray[i].calibrate(actualCoordinates[i][0], actualCoordinates[i][1], actualCoordinates[i][2]);
      }
      delay(1000);
      for(int i = 0; i < 4; i++){
        legArray[i].init();
      }
      delay(1000);
}

void Spider::creepGait(){

}