int MOTOR1[3] = {9, 10, 11};
int MOTOR2[3] = {3, 5, 6};

int STATE1[3] = {0, 0, 255};  // Determine the STATE2 of the windings in a variable reluctance motor
int STATE2[3] = {0, 0, 255};  // Determine the STATE2 of the windings in a variable reluctance motor


void setup() {
  Serial.begin(4800);
  while (!Serial) { ; }
  Serial.print("hello world!");
  for (int i=0 ; i < 32 ; i++) {
    pinMode(i, OUTPUT);
  }
  for (int i=0 ; i < 32 ; i++) {
    analogWrite(i, 255);
  } 
  for (int i=0 ; i < 3 ; i++) {
    analogWrite(MOTOR1[i], STATE2[i]);
    analogWrite(MOTOR2[i], STATE2[i]);
  }
}

int get_high_pin(int rightmost=1) {
  // Return the index of the pin with the highest value
  // In the case of a tie, where two pins are equally high,
  // choose either a rightmost or leftmost high pin.
  // assuming pins are located in a line,
  // it determines whether to get the high pin
  // on the leftmost side (rightmost=0)
  // or on the rightmost side (rightmost=1)
  
  int argmax = 0;
  for (int i=0 ; i < 3 ; i++) {
    if (rightmost == 0) {
      i = 2 - i;
    }
    if (STATE2[i] > STATE2[argmax]) {
      argmax = i;
    }
  }
  return argmax;
}

void write_STATE2() {
  for (int i=0 ; i<3 ; i++) {
    Serial.print(i, DEC);
    Serial.print(" ");
    Serial.println(STATE2[i], DEC);
  }
  Serial.println("---");

}

void step_left(int motor_num) {
  int *motor;
  int *state;
  if (motor_num == 1) {
    motor = MOTOR1;
    state = STATE1;
  } else { //(motor_num == 2) {
    motor = MOTOR2;
    state = STATE2;
  }
  // Get left most high pin
  int j = get_high_pin(1);
  
  int i = (j + 2) % 3;
  int k = (j + 1) % 3;

if (state[i] < state[k]) {
    state[k] -= 1;
    analogWrite(motor[k], state[k]);
  } else if (state[i] == state[k]) {  // both neighbors i and k == 0
    state[i] += 1;
    analogWrite(motor[i], state[i]);
  } else { // (state[i] > state[k]) {
    if (state[i] == state[j]) {  // both i and j == 255
      state[j] -= 1;
      analogWrite(motor[j], state[j]);
    } else {
      state[i] += 1;
      analogWrite(motor[i], state[i]);
    }
  }
}
  
void step_right(int motor_num) {
  int *motor;
  int *state;
  if (motor_num == 1) {
    motor = MOTOR1;
    state = STATE1;
  } else { //(motor_num == 2) {
    motor = MOTOR2;
    state = STATE2;
  }
  // Get right most high pin
  int j = get_high_pin(1);
  
  int i = (j + 2) % 3;  // pin to left
  int k = (j + 1) % 3;  // pin to right
  
  if (state[i] > state[k]) {
    // either i == j or i < j.  In both cases, decrement i
    state[i] -= 1;
    analogWrite(motor[i], state[i]);
  } else if (state[i] == state[k]) {
    // both neighbor pins are 0
    // increment k
    state[k] += 1;
    analogWrite(motor[k], state[k]);
  } else { // i < k
    // either k == j (both are 255) or k < j
    if (state[k] == state[j]) {
      // decrement j
      state[j] -= 1;
      analogWrite(motor[j], state[j]);
    } else {
      // increment k
      state[k] += 1;
      analogWrite(motor[k], state[k]);
    }
  }
}
  
int del = 5;
void loop() {
  for (int i=0 ; i < 100 ; i++) {
  delay(del);
  step_right(1);
  step_right(2);
  delay(del);
  step_right(1);
  step_right(2);
  delay(del);
  step_right(1);
  step_right(2);
  delay(del);
  }
  for (int i=0 ; i < 100 ; i++) {
  step_left(1);
  step_left(2);
  delay(del);
  step_left(1);
  step_left(2);
  }
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
