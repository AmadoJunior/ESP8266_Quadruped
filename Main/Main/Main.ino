#include "Leg.h"
#include "Spider.h"

//Init
Spider mySpider(1);

void setup() {
  Serial.begin(9600);
  mySpider.initPwm();
  mySpider.initCalibration();
  
}

void loop() {
  //delay(2000);  
  //mySpider.creepGait();
}
