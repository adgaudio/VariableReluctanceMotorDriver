#include <stdint.h>


class VariableReluctanceDriver {
  int *motor;
  int *state;

  void (*write_pin_callback)(uint8_t pin, int val);

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
      if (state[i] > state[argmax]) {
        argmax = i;
      }
    }
    return argmax;
  }

  void step(bool left=false) {
    // Get right most high pin
    int j = get_high_pin(1);

    int i = (j + 2) % 3;  // pin to left
    int k = (j + 1) % 3;  // pin to right

    if (left) {
      int _ik = i;
      i = k;
      k = _ik;
    }

    if (state[i] > state[k]) {
      // either i == j or i < j.  In both cases, decrement i
      state[i] -= 1;
      write_pin_callback(motor[i], state[i]);
    } else if (state[i] == state[k]) {
      // both neighbor pins are 0
      // increment k
      state[k] += 1;
      write_pin_callback(motor[k], state[k]);
    } else { // i < k
      // either k == j (both are 255) or k < j
      if (state[k] == state[j]) {
        // decrement j
        state[j] -= 1;
        write_pin_callback(motor[j], state[j]);
      } else {
        // increment k
        state[k] += 1;
        write_pin_callback(motor[k], state[k]);
      }
    }
  }

  public:
    VariableReluctanceDriver(int (&_motor)[3], int (&_state)[3], void (*_write_pin_callback)(uint8_t pin, int val)) {
      this->motor = _motor;  // Identify which pins map to each winding in the motor
      this->state = _state;  // Determine the STATE of the windings in a variable reluctance motor
      this->write_pin_callback = _write_pin_callback;  // A callback that writes a pin value to the assigned motor pin

      for (int i=0 ; i < 3 ; i++) {
        write_pin_callback(motor[i], state[i]);
      }
    }

    void step_right(int num_steps=1) {
      for (int i=0 ; i < num_steps ; i++) {
        step(false);
      }
    }

    void step_left(int num_steps=1) {
      for (int i=0 ; i < num_steps ; i++) {
        step(true);
      }
    }
};

