#include <Firmata.h>
#include "driver.cpp"


int MOTOR1[3] = {9, 10, 11};
int MOTOR2[3] = {3, 5, 6};
int STATE1[3] = {0, 0, 255};
int STATE2[3] = {0, 255, 0};

VariableReluctanceDriver motor1 = VariableReluctanceDriver(
  MOTOR1, STATE1, analogWrite);
VariableReluctanceDriver motor2 = VariableReluctanceDriver(
  MOTOR2, STATE2, analogWrite);

void setup() {
  // initialize Firmata
  Firmata.setFirmwareVersion(0, 2);
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
}

void main_callback(byte motor1_steps, signed int motor2_steps) {
  // A callback that executes on a serial message
  // motor1_steps is actually a signed int, but Firmata expects a byte in the function sign
  int m1 = motor1_steps;
  if (m1 > 0) {
    motor1.step_right(m1);
  } else { motor1.step_left(m1); }
  
  if (motor2_steps > 0) {
    motor2.step_right(motor2_steps);
  } else { motor2.step_left(motor2_steps); }
}
