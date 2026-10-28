/*
  10 - Control ONE BO Motor with the Adafruit L293D Motor Shield (V1)
  Board: Arduino Uno

  Libraries required:
    - "Adafruit Motor Shield library" (V1, AFMotor.h) version 1.0.1
      (Do NOT install the "V2" library, it is for a different shield.)

  Wiring:
    Plug the shield on top of the Uno.
    Motor wires -> M1 terminal.
    Battery     -> EXT_PWR terminal (4.5V to 12V).

  If the motor spins the wrong way, swap its two wires.
*/

#include <AFMotor.h>   // Library for the V1 motor shield

AF_DCMotor motor(1);   // Motor connected to the M1 terminal

void setup() {
  motor.setSpeed(200);   // Speed from 0 (stop) to 255 (full speed)
}

void loop() {
  motor.run(FORWARD);    // Spin forward...
  delay(2000);           // ...for 2 seconds

  motor.run(RELEASE);    // Stop the motor...
  delay(1000);           // ...for 1 second

  motor.run(BACKWARD);   // Spin backward...
  delay(2000);           // ...for 2 seconds

  motor.run(RELEASE);    // Stop again...
  delay(1000);           // ...for 1 second
}
