#include <Firmata.h>
#include "driver.cpp"

int joystick_high_pin = 1; // power to joystick switches
int joystick_left_pin = 2; // wrong pin!?
int joystick_right_pin = 4; // wrong pin!?
int joystick_up_pin = 7; // wrong pin!?
int joystick_down_pin = 8; // wrong pin!? 

int MOTOR1[3] = {9, 10, 11};
int MOTOR2[3] = {3, 5, 6};
int STATE1[3] = {0, 0, 255};
int STATE2[3] = {0, 255, 0};

VariableReluctanceDriver motor1 = VariableReluctanceDriver(
  MOTOR1, STATE1, analogWrite);
VariableReluctanceDriver motor2 = VariableReluctanceDriver(
  MOTOR2, STATE2, analogWrite);

VariableReluctanceDriver MOTORS[] = {motor1, motor2};


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
  
  // set the joystick read pins
  digitalWrite(joystick_high_pin, HIGH);
  pinMode(joystick_left_pin, INPUT);
  pinMode(joystick_right_pin, INPUT);
  pinMode(joystick_up_pin, INPUT);
  pinMode(joystick_down_pin, INPUT);
  // 1 2 4 7 8 12-36
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.print('A');   // send a capital A
    delay(300);
  }
}

void loop() {
//  byte arr[2] = {254, 254};
//  main_callback(3, 2, arr);
//  delay(500);
//  main_callback(0, 2, arr);
//  delay(500);
//  establishContact();

//  while(Firmata.available()) {
//    Firmata.processInput();
//  }
  if (digitalRead(joystick_left_pin) == HIGH) {
    MOTORS[0].step_left(1);
  }
  if (digitalRead(joystick_right_pin) == HIGH) {
    MOTORS[0].step_right(1);
  }
  if (digitalRead(joystick_up_pin) == HIGH) {
    MOTORS[1].step_left(1);
  }
  if (digitalRead(joystick_down_pin) == HIGH) {
    MOTORS[1].step_right(1);
  }
}

void main_callback(byte dir, byte _num_bytes_sent, byte *num_steps) {
  /* Move motors a given number of steps in some direction

     `dir` - a byte where each bit corresponds to the direction
        of a specific motor.  1 means step right.  0 means step left.
        The nth bit starting from least significant (right) corresponds to the
        nth motor in MOTORS
     `_num_bytes_sent` - a number of motors being coordinated.  aka the size of
        `num_steps`
     `num_steps` - an array of bytes where the nth byte corresponds to the nth
        motor.  Each byte determines an int8 number of steps that the motor
        can move
  */
  int num_bytes_sent = _num_bytes_sent;
  if (num_bytes_sent > 8) {
    num_bytes_sent = 8;
  }
  for (int i=0 ; i<num_bytes_sent ; i++) {
    if (((dir>>i) | 0) == 0) {
      MOTORS[i].step_right(num_steps[i]);
    } else if (((dir>>i) & 1) == 1) {
      MOTORS[i].step_left(num_steps[i]);
    } else {
      while (1) {; }
    }
  }
}

