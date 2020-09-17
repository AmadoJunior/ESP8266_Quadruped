#include "Leg.h"
#include "Spider.h"

//Init
Spider mySpider(1);

void setup() {
  mySpider.initPwm();
  Serial.begin(9600);
}

void loop() {
  delay(2000);  
  mySpider.creepGait();
}
