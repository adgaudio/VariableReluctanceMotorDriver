#include <Firmata.h>
#include "driver.cpp"


int MOTOR1[3] = {9, 10, 11};
int MOTOR2[3] = {3, 5, 6};
int STATE1[3] = {0, 0, 255};
int STATE2[3] = {0, 0, 255};

VariableReluctanceDriver motor1 = VariableReluctanceDriver(
  MOTOR1, STATE1, analogWrite);
VariableReluctanceDriver motor2 = VariableReluctanceDriver(
  MOTOR2, STATE2, analogWrite);
  

void setup() {
  // initialize Firmata
  Firmata.setFirmwareVersion(0, 1);
  Firmata.attach(ANALOG_MESSAGE, main_callback);
  Firmata.begin(57600);

  // clear all pins
  for (int i=0 ; i < 32 ; i++) {
    pinMode(i, OUTPUT);
  }
  for (int i=0 ; i < 32 ; i++) {
    analogWrite(i, 255);
  }
}

void loop() {
  while(Firmata.available()) {
    Firmata.processInput();
  }
//  for(analogPin = 0; analogPin < TOTAL_ANALOG_PINS; analogPin++) {
//      Firmata.sendAnalog(analogPin, analogRead(analogPin)); 
//  }
}

void main_callback(byte pin, int value) {
  // A callback that executes on a serial message

  if (pin == 0) {
    motor1.step_left();
  } else if (pin == 1) {
    motor1.step_right();
  }
  motor2.step_right();
//  for (int i=0 ; i < 100 ; i++) {
//  delay(del);
//  step_right(1);
//  step_right(2);
//  delay(del);
//  step_right(1);
//  step_right(2);
//  delay(del);
//  step_right(1);
//  step_right(2);
//  delay(del);
//  }
//  for (int i=0 ; i < 100 ; i++) {
//  step_left(1);
//  step_left(2);
//  delay(del);
//  step_left(1);
//  step_left(2);
//  }
  //delay(1000);

}

/*
NOTES:

Motor 15 > motor1_pins > 7
a 9
b 10
c 11
Motor 2 < 7
a 3
b 5
c 6
*/
