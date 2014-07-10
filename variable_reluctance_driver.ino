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
  // Firmata.attach(ANALOG_MESSAGE, main_callback);
  Firmata.attach(START_SYSEX, main_callback);
  Firmata.begin(57600);

  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // clear all pins
  for (int i=0 ; i < 32 ; i++) {
    pinMode(i, OUTPUT);
  }
  for (int i=0 ; i < 32 ; i++) {
    analogWrite(i, 255);
  }
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.print('A');   // send a capital A
    delay(300);
  }
}

void loop() {
  establishContact();

  while(Firmata.available()) {
    Firmata.processInput();   
  }                           
}

void main_callback(byte num_motors, byte num_bytes_sent, byte *num_steps) {
  // A callback that executes on a serial message
  // motor1_steps is actually a signed int, but Firmata expects a byte in the function sign
 
  // TODO: basically, just figure out how to assign motor1 to n steps right or left and do the same with motor2
  
  double num_steps = num_steps[1];
  if (num_motors & 1 == 1) {
    motor1.step_right(num_steps)
  } elif (num_motors & 3 == 2) {
    motor1.step_left(num_steps);
  }
  if (num_motors & 3) {
    motor2.step_right
  for (i < num_bytes_sent ; i++) {
  }
  int m1 = motor1_steps;
  if (m1 > 0) {
    motor1.step_right(m1);
  } else { motor1.step_left(m1); }

  if (motor2_steps > 0) {
    motor2.step_right(motor2_steps);
  } else { motor2.step_left(motor2_steps); }
}
