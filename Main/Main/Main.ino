#include "Leg.h"
#include "Spider.h"

//Init
Spider mySpider(1);

void setup() {
  Serial.begin(9600);
  mySpider.initPwm();
  delay(500);
  mySpider.initCalibration();
  
}

void loop() {
  mySpider.creepGait();
}
