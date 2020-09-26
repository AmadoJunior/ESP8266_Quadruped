#include "Spider.h"

unsigned long startTime;
unsigned long curTime;

Spider::Spider(int n){
    frequency = 50;

    //Populating legArray ===========================
      int count = 0;
      for(int i = 0; i < 12; i+=3){
        legArray[count].setPins(i, i+1, i+2);
        legArray[count].setLegNum(count+1);
        count++;
      }
      a = &Spider::legArray[0];
      b = &Spider::legArray[1];
      c = &Spider::legArray[2];
      d = &Spider::legArray[3];
}

void Spider::initPwm(){
  
    for(int i = 0; i < 4; i++){
        legArray[i].pwm.begin();
        legArray[i].pwm.setPWMFreq(frequency);
    }
    delay(1000);
    a->init();
    b->init();
    c->init();
    d->init();
    Serial.println("Init PWM");
}

void Spider::initCalibration(){
  //Calibration =====================
      /*
      Expected:  
                x: 100, y: 80, z: 45
      */
      float actualCoordinates[4][3] = {
        {-100,95,40},
        {-110,-60,55},
        {105,55,80},
        {112,-90,38}
      };
      for(int i = 0; i < 4; i++){
          legArray[i].calibrate(actualCoordinates[i][0], actualCoordinates[i][1], actualCoordinates[i][2]);
      }
      delay(500);
      for(int i = 0; i < 4; i++){
        legArray[i].init();
        delay(500);
      }
      Serial.println("Init Calibration");
      delay(500);
}

void Spider::updateAllGradual(bool liftA, bool liftB, bool liftC, bool liftD){

  if(liftA){
    a->curCoordinates.z += 20;
    a->setAngles(a->curCoordinates.x, a->curCoordinates.y, a->curCoordinates.z);
    a->updatePos();
    delay(10);
  } 
  if(liftB){
    b->curCoordinates.z += 20;
    b->setAngles(b->curCoordinates.x, b->curCoordinates.y, b->curCoordinates.z);
    b->updatePos();
    delay(10);
  } 
  if(liftC){
    c->curCoordinates.z += 20;
    c->setAngles(c->curCoordinates.x, c->curCoordinates.y, c->curCoordinates.z);
    c->updatePos();
    delay(10);
  } 
  if(liftD){
    d->curCoordinates.z += 20;
    d->setAngles(d->curCoordinates.x, d->curCoordinates.y, d->curCoordinates.z);
    d->updatePos();
    delay(10);
  } 

  while(a->curCoordinates.x != a->desiredCoordinates.x ||
        a->curCoordinates.y != a->desiredCoordinates.y ||
        a->curCoordinates.z != a->desiredCoordinates.z ||
        b->curCoordinates.x != b->desiredCoordinates.x ||
        b->curCoordinates.y != b->desiredCoordinates.y ||
        b->curCoordinates.z != b->desiredCoordinates.z ||
        c->curCoordinates.x != c->desiredCoordinates.x ||
        c->curCoordinates.y != c->desiredCoordinates.y ||
        c->curCoordinates.z != c->desiredCoordinates.z || 
        d->curCoordinates.x != d->desiredCoordinates.x ||
        d->curCoordinates.y != d->desiredCoordinates.y ||
        d->curCoordinates.z != d->desiredCoordinates.z
        ){
          // Serial.println(a->curCoordinates.x);
          // Serial.println(a->curCoordinates.y);
          // Serial.println(a->curCoordinates.z);
          // Serial.println();

          //X
          (a->curCoordinates.x != a->desiredCoordinates.x) ? 
            a->setCurCoordinateX(a->curCoordinates.x > a->desiredCoordinates.x ? a->curCoordinates.x-1: a->curCoordinates.x+1) : false;
          (b->curCoordinates.x != b->desiredCoordinates.x) ?  
            b->setCurCoordinateX(b->curCoordinates.x > b->desiredCoordinates.x ? b->curCoordinates.x-1: b->curCoordinates.x+1) : false;
          (c->curCoordinates.x != c->desiredCoordinates.x) ? 
            c->setCurCoordinateX(c->curCoordinates.x > c->desiredCoordinates.x ? c->curCoordinates.x-1: c->curCoordinates.x+1) : false;
          (d->curCoordinates.x != d->desiredCoordinates.x) ? 
            d->setCurCoordinateX(d->curCoordinates.x > d->desiredCoordinates.x ? d->curCoordinates.x-1: d->curCoordinates.x+1) : false;
          //Y
          (a->curCoordinates.y != a->desiredCoordinates.y) ? 
            a->setCurCoordinateY(a->curCoordinates.y > a->desiredCoordinates.y ? a->curCoordinates.y-1: a->curCoordinates.y+1) : false;
          (b->curCoordinates.y != b->desiredCoordinates.y) ?  
            b->setCurCoordinateY(b->curCoordinates.y > b->desiredCoordinates.y ? b->curCoordinates.y-1: b->curCoordinates.y+1) : false;
          (c->curCoordinates.y != c->desiredCoordinates.y) ? 
            c->setCurCoordinateY(c->curCoordinates.y > c->desiredCoordinates.y ? c->curCoordinates.y-1: c->curCoordinates.y+1) : false;
          (d->curCoordinates.y != d->desiredCoordinates.y) ? 
            d->setCurCoordinateY(d->curCoordinates.y > d->desiredCoordinates.y ? d->curCoordinates.y-1: d->curCoordinates.y+1) : false;
          //Z
          (a->curCoordinates.z != a->desiredCoordinates.z) ? 
            a->setCurCoordinateZ(a->curCoordinates.z > a->desiredCoordinates.z ? a->curCoordinates.z-0.5: a->curCoordinates.z+0.5) : false;
          (b->curCoordinates.z != b->desiredCoordinates.z) ?  
            b->setCurCoordinateZ(b->curCoordinates.z > b->desiredCoordinates.z ? b->curCoordinates.z-0.5: b->curCoordinates.z+0.5) : false;
          (c->curCoordinates.z != c->desiredCoordinates.z) ? 
            c->setCurCoordinateZ(c->curCoordinates.z > c->desiredCoordinates.z ? c->curCoordinates.z-0.5: c->curCoordinates.z+0.5) : false;
          (d->curCoordinates.z != d->desiredCoordinates.z) ? 
            d->setCurCoordinateZ(d->curCoordinates.z > d->desiredCoordinates.z ? d->curCoordinates.z-0.5: d->curCoordinates.z+0.5) : false;

          //Setting Angles and Updating
          a->setAngles(a->curCoordinates.x, a->curCoordinates.y, a->curCoordinates.z);
          b->setAngles(b->curCoordinates.x, b->curCoordinates.y, b->curCoordinates.z);
          c->setAngles(c->curCoordinates.x, c->curCoordinates.y, c->curCoordinates.z);
          d->setAngles(d->curCoordinates.x, d->curCoordinates.y, d->curCoordinates.z);
          c->updatePos();
          b->updatePos();
          a->updatePos();
          d->updatePos();
          //delay(5);
        }
  
}

void Spider::standBy(){
  a->setDesiredCoordinates(-65,65,-80);
  b->setDesiredCoordinates(-65,-65,-80);
  c->setDesiredCoordinates(65,65,-80);
  d->setDesiredCoordinates(65,-65,-80);
  updateAllGradual(false, false,  false, false);
}

void Spider::sit(){
  a->setDesiredCoordinates(-81,81,0);
  b->setDesiredCoordinates(-81,-81,0);
  c->setDesiredCoordinates(81,81,0);
  d->setDesiredCoordinates(81,-81,0);
  updateAllGradual(false, false,  false, false);
}

void Spider::creepGait(){
  //standBy
  a->setDesiredCoordinates(-80,80,-40);
  b->setDesiredCoordinates(-80,-80,-40);
  c->setDesiredCoordinates(80,80,-40);
  d->setDesiredCoordinates(80,-80,-40);
  updateAllGradual(false, false,  false, false);
  delay(1000);
  c->moveLeg(80, 0, -60, true);

  startTime = millis();
  while(true){
    curTime = millis();
    if(curTime - startTime > 5000){
      break;
    }
    //Step 1
    d->moveLeg(80, 0, -60, true);
    //Step 2
    c->moveLeg(c->curCoordinates.x,c->curCoordinates.y + 120 ,c->curCoordinates.z, true);
    //Step 3
    a->setDesiredCoordinates(a->curCoordinates.x,a->curCoordinates.y - 60 ,a->curCoordinates.z);
    b->setDesiredCoordinates(b->curCoordinates.x,b->curCoordinates.y - 60 ,b->curCoordinates.z);
    c->setDesiredCoordinates(c->curCoordinates.x,c->curCoordinates.y - 60 ,c->curCoordinates.z);
    d->setDesiredCoordinates(d->curCoordinates.x,d->curCoordinates.y - 60 ,d->curCoordinates.z);
    updateAllGradual(false, false,  false, false);
    //Step 4
    b->moveLeg(b->curCoordinates.x,b->curCoordinates.y + 120 ,b->curCoordinates.z, true);
    a->moveLeg(b->curCoordinates.x,b->curCoordinates.y + 120 ,b->curCoordinates.z, true);
    //Step 5
    a->setDesiredCoordinates(a->curCoordinates.x,a->curCoordinates.y - 60 ,a->curCoordinates.z);
    b->setDesiredCoordinates(b->curCoordinates.x,b->curCoordinates.y - 60 ,b->curCoordinates.z);
    c->setDesiredCoordinates(c->curCoordinates.x,c->curCoordinates.y - 60 ,c->curCoordinates.z);
    d->setDesiredCoordinates(d->curCoordinates.x,d->curCoordinates.y - 60 ,d->curCoordinates.z);
    updateAllGradual(false, false,  false, false);
    //Step 6
    d->moveLeg(d->curCoordinates.x,d->curCoordinates.y + 120 ,d->curCoordinates.z, true);
  }
  
}

void Spider::trotSetUp(String dir, bool rotate){
  standBy();
  delay(200);
  Serial.println("trotting...");
  if(!rotate){
    if(dir == "up"){
      //SetUp Step
      a->setDesiredCoordinates(a->curCoordinates.x, a->curCoordinates.y-15, a->curCoordinates.z);
      d->setDesiredCoordinates(d->curCoordinates.x, d->curCoordinates.y-15, d->curCoordinates.z);
      c->setDesiredCoordinates(c->curCoordinates.x, c->curCoordinates.y+15, c->curCoordinates.z);
      b->setDesiredCoordinates(b->curCoordinates.x, b->curCoordinates.y+15, b->curCoordinates.z);
      updateAllGradual(false,  true, true, false);
    } else if(dir == "down"){
      a->setDesiredCoordinates(a->curCoordinates.x, a->curCoordinates.y+15, a->curCoordinates.z);
      d->setDesiredCoordinates(d->curCoordinates.x, d->curCoordinates.y+15, d->curCoordinates.z);
      c->setDesiredCoordinates(c->curCoordinates.x, c->curCoordinates.y-15, c->curCoordinates.z);
      b->setDesiredCoordinates(b->curCoordinates.x, b->curCoordinates.y-15, b->curCoordinates.z);
      updateAllGradual(false,  true, true, false);
    } else if(dir == "left"){
      a->setDesiredCoordinates(a->curCoordinates.x+15, a->curCoordinates.y, a->curCoordinates.z);
      d->setDesiredCoordinates(d->curCoordinates.x+15, d->curCoordinates.y, d->curCoordinates.z);
      c->setDesiredCoordinates(c->curCoordinates.x-15, c->curCoordinates.y, c->curCoordinates.z);
      b->setDesiredCoordinates(b->curCoordinates.x-15, b->curCoordinates.y, b->curCoordinates.z);
      updateAllGradual(false,  true, true, false);
    } else if(dir == "right"){
      a->setDesiredCoordinates(a->curCoordinates.x-15, a->curCoordinates.y, a->curCoordinates.z);
      d->setDesiredCoordinates(d->curCoordinates.x-15, d->curCoordinates.y, d->curCoordinates.z);
      c->setDesiredCoordinates(c->curCoordinates.x+15, c->curCoordinates.y, c->curCoordinates.z);
      b->setDesiredCoordinates(b->curCoordinates.x+15, b->curCoordinates.y, b->curCoordinates.z);
      updateAllGradual(false,  true, true, false);
    }
  } else {
    if(dir == "left"){
      a->setDesiredCoordinates(a->curCoordinates.x, a->curCoordinates.y-15, a->curCoordinates.z);
      d->setDesiredCoordinates(d->curCoordinates.x, d->curCoordinates.y+15, d->curCoordinates.z);
      c->setDesiredCoordinates(c->curCoordinates.x, c->curCoordinates.y-15, c->curCoordinates.z);
      b->setDesiredCoordinates(b->curCoordinates.x, b->curCoordinates.y+15, b->curCoordinates.z);
      updateAllGradual(false,  true, true, false);
    } else if(dir == "right") {
      a->setDesiredCoordinates(a->curCoordinates.x, a->curCoordinates.y+15, a->curCoordinates.z);
      d->setDesiredCoordinates(d->curCoordinates.x, d->curCoordinates.y-15, d->curCoordinates.z);
      c->setDesiredCoordinates(c->curCoordinates.x, c->curCoordinates.y+15, c->curCoordinates.z);
      b->setDesiredCoordinates(b->curCoordinates.x, b->curCoordinates.y-15, b->curCoordinates.z);
      updateAllGradual(false,  true, true, false);
    }
  }
  
}

void Spider::trotGait(String dir, bool rotate){
  if(!rotate){
    if(dir == "up"){
      //Step 1
      //Serial.println("Trooting");
      a->setDesiredCoordinates(a->curCoordinates.x, a->curCoordinates.y+30, a->curCoordinates.z);
      d->setDesiredCoordinates(d->curCoordinates.x, d->curCoordinates.y+30, d->curCoordinates.z);
      c->setDesiredCoordinates(c->curCoordinates.x, c->curCoordinates.y-30, c->curCoordinates.z);
      b->setDesiredCoordinates(b->curCoordinates.x, b->curCoordinates.y-30, b->curCoordinates.z);
      updateAllGradual(true,  false, false, true);

      a->setDesiredCoordinates(a->curCoordinates.x, a->curCoordinates.y-30, a->curCoordinates.z);
      d->setDesiredCoordinates(d->curCoordinates.x, d->curCoordinates.y-30, d->curCoordinates.z);
      c->setDesiredCoordinates(c->curCoordinates.x, c->curCoordinates.y+30, c->curCoordinates.z);
      b->setDesiredCoordinates(b->curCoordinates.x, b->curCoordinates.y+30, b->curCoordinates.z);
      updateAllGradual(false,  true, true, false);
    } else if(dir == "down"){
      //Step 1
      //Serial.println("Trooting");
      a->setDesiredCoordinates(a->curCoordinates.x, a->curCoordinates.y-30, a->curCoordinates.z);
      d->setDesiredCoordinates(d->curCoordinates.x, d->curCoordinates.y-30, d->curCoordinates.z);
      c->setDesiredCoordinates(c->curCoordinates.x, c->curCoordinates.y+30, c->curCoordinates.z);
      b->setDesiredCoordinates(b->curCoordinates.x, b->curCoordinates.y+30, b->curCoordinates.z);
      updateAllGradual(true,  false, false, true);

      a->setDesiredCoordinates(a->curCoordinates.x, a->curCoordinates.y+30, a->curCoordinates.z);
      d->setDesiredCoordinates(d->curCoordinates.x, d->curCoordinates.y+30, d->curCoordinates.z);
      c->setDesiredCoordinates(c->curCoordinates.x, c->curCoordinates.y-30, c->curCoordinates.z);
      b->setDesiredCoordinates(b->curCoordinates.x, b->curCoordinates.y-30, b->curCoordinates.z);
      updateAllGradual(false,  true, true, false);
    } else if(dir == "left"){
      //Step 1
      //Serial.println("Trooting");
      a->setDesiredCoordinates(a->curCoordinates.x-30, a->curCoordinates.y, a->curCoordinates.z);
      d->setDesiredCoordinates(d->curCoordinates.x-30, d->curCoordinates.y, d->curCoordinates.z);
      c->setDesiredCoordinates(c->curCoordinates.x+30, c->curCoordinates.y, c->curCoordinates.z);
      b->setDesiredCoordinates(b->curCoordinates.x+30, b->curCoordinates.y, b->curCoordinates.z);
      updateAllGradual(true,  false, false, true);

      a->setDesiredCoordinates(a->curCoordinates.x+30, a->curCoordinates.y, a->curCoordinates.z);
      d->setDesiredCoordinates(d->curCoordinates.x+30, d->curCoordinates.y, d->curCoordinates.z);
      c->setDesiredCoordinates(c->curCoordinates.x-30, c->curCoordinates.y, c->curCoordinates.z);
      b->setDesiredCoordinates(b->curCoordinates.x-30, b->curCoordinates.y, b->curCoordinates.z);
      updateAllGradual(false,  true, true, false);
    } else if(dir == "right"){
      //Step 1
      //Serial.println("Trooting");
      a->setDesiredCoordinates(a->curCoordinates.x+30, a->curCoordinates.y, a->curCoordinates.z);
      d->setDesiredCoordinates(d->curCoordinates.x+30, d->curCoordinates.y, d->curCoordinates.z);
      c->setDesiredCoordinates(c->curCoordinates.x-30, c->curCoordinates.y, c->curCoordinates.z);
      b->setDesiredCoordinates(b->curCoordinates.x-30, b->curCoordinates.y, b->curCoordinates.z);
      updateAllGradual(true,  false, false, true);

      a->setDesiredCoordinates(a->curCoordinates.x-30, a->curCoordinates.y, a->curCoordinates.z);
      d->setDesiredCoordinates(d->curCoordinates.x-30, d->curCoordinates.y, d->curCoordinates.z);
      c->setDesiredCoordinates(c->curCoordinates.x+30, c->curCoordinates.y, c->curCoordinates.z);
      b->setDesiredCoordinates(b->curCoordinates.x+30, b->curCoordinates.y, b->curCoordinates.z);
      updateAllGradual(false,  true, true, false);
    }
  } else {
    if(dir == "left"){
      a->setDesiredCoordinates(a->curCoordinates.x, a->curCoordinates.y+30, a->curCoordinates.z);
      d->setDesiredCoordinates(d->curCoordinates.x, d->curCoordinates.y-30, d->curCoordinates.z);
      c->setDesiredCoordinates(c->curCoordinates.x, c->curCoordinates.y+30, c->curCoordinates.z);
      b->setDesiredCoordinates(b->curCoordinates.x, b->curCoordinates.y-30, b->curCoordinates.z);
      updateAllGradual(true,  false, false, true);
      a->setDesiredCoordinates(a->curCoordinates.x, a->curCoordinates.y-30, a->curCoordinates.z);
      d->setDesiredCoordinates(d->curCoordinates.x, d->curCoordinates.y+30, d->curCoordinates.z);
      c->setDesiredCoordinates(c->curCoordinates.x, c->curCoordinates.y-30, c->curCoordinates.z);
      b->setDesiredCoordinates(b->curCoordinates.x, b->curCoordinates.y+30, b->curCoordinates.z);
      updateAllGradual(false,  true, true, false);
    } else if(dir == "right") {
      a->setDesiredCoordinates(a->curCoordinates.x, a->curCoordinates.y-30, a->curCoordinates.z);
      d->setDesiredCoordinates(d->curCoordinates.x, d->curCoordinates.y+30, d->curCoordinates.z);
      c->setDesiredCoordinates(c->curCoordinates.x, c->curCoordinates.y-30, c->curCoordinates.z);
      b->setDesiredCoordinates(b->curCoordinates.x, b->curCoordinates.y+30, b->curCoordinates.z);
      updateAllGradual(true,  false, false, true);
      a->setDesiredCoordinates(a->curCoordinates.x, a->curCoordinates.y+30, a->curCoordinates.z);
      d->setDesiredCoordinates(d->curCoordinates.x, d->curCoordinates.y-30, d->curCoordinates.z);
      c->setDesiredCoordinates(c->curCoordinates.x, c->curCoordinates.y+30, c->curCoordinates.z);
      b->setDesiredCoordinates(b->curCoordinates.x, b->curCoordinates.y-30, b->curCoordinates.z);
      updateAllGradual(false,  true, true, false);
    }
  }

} 