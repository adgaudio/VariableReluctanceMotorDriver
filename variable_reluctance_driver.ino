#include <Firmata.h>
#include "driver.cpp"

/* 2,4,7,12,13,14,15,16 */
int joystick_left_pin = 2;
/* int joystick_power_pin = 1; // power to joystick switches */
int joystick_down_pin = 4;
int joystick_fire_pin = 7;
int joystick_up_pin = 12;
int joystick_right_pin = 13;

/* int joystick_fire_pin = 2; // the red button */
/* int joystick_power_pin = 2; // power to joystick switches */
/* int joystick_left_pin = 1; */
/* int joystick_right_pin = 6; */
/* int joystick_up_pin = 5; */
/* int joystick_down_pin = 3; */


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
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // clear all pins
  for (int i=0 ; i < 32 ; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
    pinMode(i, INPUT);
  }
  for (int i=0; i<3; i++) {
    pinMode(MOTOR1[i], OUTPUT);
    pinMode(MOTOR2[i], OUTPUT);
    analogWrite(MOTOR1[i], STATE1[i]);
    analogWrite(MOTOR2[i], STATE1[i]);
  }

  /* for (int x = 0 ; x <= 36 ; x++) { */
    /* Serial.println((String) "pin " + x + " " + digitalRead(x)); */
  /* } */

  // set the joystick read pins
  // TODO
  /* digitalWrite(joystick_power_pin, HIGH); */
  /* pinMode(joystick_left_pin, INPUT); */
  /* pinMode(joystick_right_pin, INPUT); */
  /* pinMode(joystick_up_pin, INPUT); */
  /* pinMode(joystick_down_pin, INPUT); */
  // 1 2 4 7 8 12-36
}

void loop() {
  /*
   * default HIGH are:  0, 15, 16, 23, 31
   *
   * 0 --> 
   * 1 --> 
   * 2 --> INT
   * 3 --> (MOTOR)
   * 4 --> CH2
   * 5 --> (MOTOR)
   * 6 --> (MOTOR)
   * 7 --> CH3
   * 8 --> 
   * 9 --> (MOTOR)
   * 10 --> (MOTOR)
   * 11 --> (MOTOR)
   * 12 --> Pitch (hole with the arrow)
   * 13 --> Pitch (middle hole, nearest hole with arrow)
   * 14 --> (top left, A0 mentioned on under side of board)
   * 15 --> (top right, A1 mentioned on under side of board)
   * 16 --> A2
   *
   */

  /* digitalWrite(16, HIGH); */
  /* delay(500); */
  /* digitalWrite(16, LOW); */
  /* delay(500); */


//  while(Firmata.available()) {
//    Firmata.processInput();
//  }
  if (digitalRead(joystick_left_pin) == HIGH) {
    Serial.println("left");
    motor1.step_left(1);
  }
  if (digitalRead(joystick_right_pin) == HIGH) {
    Serial.println("right");
    motor1.step_right(1);
  }
  if (digitalRead(joystick_up_pin) == HIGH) {
    Serial.println("up");
    motor2.step_left(1);
  }
  if (digitalRead(joystick_down_pin) == HIGH) {
    Serial.println("down");
    motor2.step_right(1);
  }
  delay(1);
}

// loop.... if comunicating from computer
//  byte arr[2] = {254, 254};
//  main_callback(3, 2, arr);
//  delay(500);
//  main_callback(0, 2, arr);
//  delay(500);
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

