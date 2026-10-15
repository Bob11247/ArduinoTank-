#include <AFMotor.h>

AF_DCMotor motorLeft(1);
AF_DCMotor motorRight(2);

volatile boolean crash = false;

void backOut() {
  crash = true;
}

void backUp() {
  motorLeft.run(BACKWARD);
  motorRight.run(BACKWARD);
  motorLeft.setSpeed(200);
  motorRight.setSpeed(200);

  delay(2000);

  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
}

void goForward(int duration, int pwm) {
  long a, b;
  boolean move = true;

  a = millis();
  do {
    if (crash == false) {
      motorLeft.run(FORWARD);
      motorRight.run(FORWARD);
      motorLeft.setSpeed(pwm);
      motorRight.setSpeed(pwm);
    }

    if (crash == true) {
      backUp();
      crash = false;
    }

    b = millis() - a;
    if (b >= duration) {
      move = false;
    }
  } while (move == true);

  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
}

void setup() {
  pinMode(2, INPUT_PULLUP);

  attachInterrupt(0, backOut, FALLING);

  delay(5000);
}

void loop() {
  goForward(5000, 255);

  delay(2000);
}
