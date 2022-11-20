#include <AccelStepper.h>

// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define dirPin 4
#define stepPin 3
#define enPin 2
#define motorInterfaceType 1
#define dcmetr 3305
#define metr dcmetr * 10

AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

int mspeed = 270;

void runMetr() {
  stepper.move(metr);
}

void setup() {
  Serial.begin(9600);
  stepper.setEnablePin(enPin);
  stepper.setPinsInverted(true, false, false);
  stepper.setMaxSpeed(275);
  //stepper.setAcceleration(30);
  stepper.disableOutputs();
}

void loop() {
  stepper.setSpeed(mspeed);
  stepper.runSpeedToPosition();
  if (Serial.available()) {
    char ch = Serial.read();
    if (ch == 'u') {
      mspeed += 5;
    }
    if (ch == 'm') {
      runMetr();
    }
    if (ch == 'q') {
      stepper.stop();
      stepper.disableOutputs();
    }
    if (ch == 'd') {
      stepper.disableOutputs();
    }
    if (ch == 's') {
      stepper.move(dcmetr);     
    }
    if (ch == 'b') {
      stepper.moveTo(0);
    }
  }
}
