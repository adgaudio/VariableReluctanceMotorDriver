#include "driver.cpp"

int joystick_left_pin = 2;
int joystick_power_pin = 16; // power to joystick switches
int joystick_down_pin = 4;
int joystick_fire_pin = 7;
int joystick_up_pin = 14;
int joystick_right_pin = 15;

/* Output from joystick looks like this, from left to right:
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
  pinMode(joystick_power_pin, OUTPUT);
  digitalWrite(joystick_power_pin, HIGH);
  pinMode(joystick_left_pin, INPUT);
  pinMode(joystick_right_pin, INPUT);
  pinMode(joystick_up_pin, INPUT);
  pinMode(joystick_down_pin, INPUT);
  pinMode(joystick_fire_pin, INPUT);
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


// motor2 is the small one.
// motor1 is the large one.
  if (!Serial.available()) {
    return;
  }
  int instruction = (int) Serial.read();
  Serial.println(instruction);

  if (false) {
  }
  /* else if (analogRead(joystick_left_pin) == 1023) { */
  else if (instruction == 52) {
    Serial.println("        left");
    motor2.step_right(10);
  }
  /* else if (analogRead(joystick_up_pin) == 1023) { */
  else if (instruction == 49) {
    Serial.println("up");
    motor1.step_left(10);
  }
  /* else if (analogRead(joystick_down_pin) == 1023) { */
  else if (instruction == 51) {
    Serial.println("   down");
    motor1.step_right(10);
  }
  /* else if (analogRead(joystick_right_pin) == 1023) { */
  else if (instruction == 50) {
    Serial.println("             right");
    motor2.step_left(10);
  }
  /* if (analogRead(joystick_fire_pin) == 1023) { */
  if (instruction == 53) {
    Serial.println("                   fire!");
    // TODO
  }
}
