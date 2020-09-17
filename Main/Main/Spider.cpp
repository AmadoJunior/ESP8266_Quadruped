#include "Spider.h"

Spider::Spider(int n){
    frequency = 50;

    //Filling legArray
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
}

void Spider::creepGait(){

}