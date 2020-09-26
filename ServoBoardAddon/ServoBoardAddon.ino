#include "Wire.h"
#include "Adafruit_PWMServoDriver.h"
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

#define MIN_PULSE_WIDTH 575
#define MAX_PULSE_WIDTH 2450
#define FREQUENCY 50

void setup() 
{
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY);
}

int pulseWidth(int angle)
{
  int pulse_wide, analog_value;
  pulse_wide = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  return analog_value;
}

void loop() {
  pwm.setPWM(0, 0, pulseWidth(45));
  delay(1000);
  pwm.setPWM(0, 0, pulseWidth(135));
  delay(1000);
  
}
