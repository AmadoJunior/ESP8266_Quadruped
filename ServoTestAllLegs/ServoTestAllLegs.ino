//www.elegoo.com
//2018.12.19
#include <Servo.h>
/* After including the corresponding libraries,
   we can use the "class" like "Servo" created by the developer for us.
   We can use the functions and variables created in the libraries by creating 
   objects like the following "myservo" to refer to the members in ".".*/

int servoPins[4][3] = {
  {1,3,15},
  {13,12,14},
  {2,0,4},
  {5,16,9}
};

Servo myServo1;
Servo myServo2;
Servo myServo3;
Servo myServo4;
Servo myServo5;
Servo myServo6;
Servo myServo7;
Servo myServo8;
Servo myServo9;
Servo myServo10;
Servo myServo11;
Servo myServo12;

Servo legs[4][3] = {
  {myServo1,myServo2,myServo3},
  {myServo4,myServo5,myServo6},
  {myServo7,myServo8,myServo9},
  {myServo10,myServo11,myServo12}
};

void setup(){
  myServo1.attach(1);
  myServo2.attach(3);
  myServo3.attach(15);
  myServo4.attach(13);
  myServo5.attach(12);
  myServo6.attach(14);
  myServo7.attach(2);
  myServo8.attach(0);
  myServo9.attach(4);
  myServo10.attach(5);
  myServo11.attach(16);
  myServo12.attach(9);
} 
void loop(){
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 4; j++){
      legs[i][j].write(90);
      delay(2000);
    }
  }
}
