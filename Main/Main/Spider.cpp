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
      a = &Spider::legArray[0];
      b = &Spider::legArray[1];
      c = &Spider::legArray[2];
      d = &Spider::legArray[3];
}

void Spider::initPwm(){
  
    for(int i = 0; i < 4; i++){
        legArray[i].pwm.begin();
        legArray[i].pwm.setPWMFreq(frequency);
        legArray[i].init();
        delay(500);
    }
     
}

void Spider::initCalibration(){
  //Calibration =====================
      /*
      Expected:  
                x: 100, y: 80, z: 45
      */
      float actualCoordinates[4][3] = {
        {-95,85,40},
        {-110,-74,50},
        {92.5,97.5,45},
        {108,-92,33}
      };
      for(int i = 0; i < 4; i++){
          legArray[i].calibrate(actualCoordinates[i][0], actualCoordinates[i][1], actualCoordinates[i][2]);
      }
      delay(500);
      for(int i = 0; i < 4; i++){
        legArray[i].init();
      }
      delay(500);
}

void Spider::updateAllGradual(){
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
        d->curCoordinates.z != d->desiredCoordinates.z){
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
            a->setCurCoordinateZ(a->curCoordinates.z > a->desiredCoordinates.z ? a->curCoordinates.z-1: a->curCoordinates.z+1) : false;
          (b->curCoordinates.z != b->desiredCoordinates.z) ?  
            b->setCurCoordinateZ(b->curCoordinates.z > b->desiredCoordinates.z ? b->curCoordinates.z-1: b->curCoordinates.z+1) : false;
          (c->curCoordinates.z != c->desiredCoordinates.z) ? 
            c->setCurCoordinateZ(c->curCoordinates.z > c->desiredCoordinates.z ? c->curCoordinates.z-1: c->curCoordinates.z+1) : false;
          (d->curCoordinates.z != d->desiredCoordinates.z) ? 
            d->setCurCoordinateZ(d->curCoordinates.z > d->desiredCoordinates.z ? d->curCoordinates.z-1: d->curCoordinates.z+1) : false;

          //Setting Angles and Updating
          a->setAngles(a->curCoordinates.x, a->curCoordinates.y, a->curCoordinates.z);
          b->setAngles(b->curCoordinates.x, b->curCoordinates.y, b->curCoordinates.z);
          c->setAngles(c->curCoordinates.x, c->curCoordinates.y, c->curCoordinates.z);
          d->setAngles(d->curCoordinates.x, d->curCoordinates.y, d->curCoordinates.z);
          c->updatePos();
          b->updatePos();
          a->updatePos();
          d->updatePos();
          //delay(1);
        }
  
}

void Spider::standBy(){
  a->setDesiredCoordinates(-80,80,-50);
  b->setDesiredCoordinates(-80,-80,-50);
  c->setDesiredCoordinates(80,80,-53);
  d->setDesiredCoordinates(80,-80,-50);
  updateAllGradual();
}

void Spider::creepGait(){
  //standBy
  standBy();
  delay(1000);
  c->moveLeg(80, 0, -50, true);
  while(true){
    //Step 1
    d->moveLeg(80, 0, -50, true);
    //Step 2
    c->moveLeg(c->curCoordinates.x,c->curCoordinates.y + 120 ,c->curCoordinates.z, true);
    //Step 3
    a->setDesiredCoordinates(a->curCoordinates.x,a->curCoordinates.y - 60 ,a->curCoordinates.z);
    b->setDesiredCoordinates(b->curCoordinates.x,b->curCoordinates.y - 60 ,b->curCoordinates.z);
    c->setDesiredCoordinates(c->curCoordinates.x,c->curCoordinates.y - 60 ,c->curCoordinates.z);
    d->setDesiredCoordinates(d->curCoordinates.x,d->curCoordinates.y - 60 ,d->curCoordinates.z);
    updateAllGradual();
    //Step 4
    b->moveLeg(b->curCoordinates.x,b->curCoordinates.y + 120 ,b->curCoordinates.z, true);
    a->moveLeg(b->curCoordinates.x,b->curCoordinates.y + 120 ,b->curCoordinates.z, true);
    //Step 5
    a->setDesiredCoordinates(a->curCoordinates.x,a->curCoordinates.y - 60 ,a->curCoordinates.z);
    b->setDesiredCoordinates(b->curCoordinates.x,b->curCoordinates.y - 60 ,b->curCoordinates.z);
    c->setDesiredCoordinates(c->curCoordinates.x,c->curCoordinates.y - 60 ,c->curCoordinates.z);
    d->setDesiredCoordinates(d->curCoordinates.x,d->curCoordinates.y - 60 ,d->curCoordinates.z);
    updateAllGradual();
    //Step 6
    d->moveLeg(d->curCoordinates.x,d->curCoordinates.y + 120 ,d->curCoordinates.z, true);
  }
  
}