#include "Leg.h"
#include "Adafruit_PWMServoDriver.h"

#define FREQUENCY 50

class Spider{
  private:
    Leg legArray[4];
  public:
    Spider(int num){
      //Filling legArray
      int count = 0;
      for(int i = 0; i < 12; i+=3){
        legArray[count].setPins(i, i+1, i+2);
        legArray[count].setLegNum(count+1);
        legArray[count].pwm.begin();
        legArray[count].pwm.setPWMFreq(FREQUENCY);
        legArray[count].lift();
        count++;
      }
      delay(5000);
      for(int i = 0; i < 5; i++){
        legArray[i].init();
      }
      
    }
    void creepGait(){
      legArray[0].lift();
    }
};

//Init
Spider mySpider(1);

void setup() {
  //Spider mySpider;
  Serial.begin(9600);
}

void loop() {
  delay(2000);  
  mySpider.creepGait();
}
