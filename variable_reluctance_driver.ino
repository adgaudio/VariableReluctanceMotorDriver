#include <Firmata.h>
#include "driver.cpp"

void setup() {
  // initialize Serial
  Serial.begin(4800);
  while (!Serial) { ; }
  Serial.print("hello world!");
  
  // initialize Firmata
  Firmata.setFirmwareVersion(0, 1);
  Firmata.attach(ANALOG_MESSAGE, main_callback);
  
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
    // step_left
  } else if (pin == 1) {
    // step_right
  }
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
