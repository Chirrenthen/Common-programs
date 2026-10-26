/*
  08 - BO Motors with the Adafruit Motor Driver Shield (V1, L293D)
  Board: Arduino Uno

  Libraries required (install from Sketch > Include Library > Manage Libraries):
    - "Adafruit Motor Shield library" (the V1 one, header file AFMotor.h)
      by Adafruit ... version 1.0.1
    Do NOT install "Adafruit Motor Shield V2 Library". It is for a different shield.

  Wiring:
    - Plug the shield on top of the Uno.
    - Motor 1 -> M1 terminal, Motor 2 -> M2 terminal.
    - Power the shield from the external terminal block (EXT_PWR, 4.5V to 12V)
      and keep the PWR jumper on the shield. BO motors need more current
      than USB can give.

  If a motor spins the wrong way, swap its two wires.
*/

#include <AFMotor.h>   // Library for the V1 motor shield

AF_DCMotor motor1(1);   // Motor connected to the M1 terminal
AF_DCMotor motor2(2);   // Motor connected to the M2 terminal

void setup() {
  motor1.setSpeed(200);   // Speed from 0 (stop) to 255 (full speed)
  motor2.setSpeed(200);
}

void loop() {
  motor1.run(FORWARD);    // Spin both motors forward
  motor2.run(FORWARD);
  delay(2000);            // Run for 2 seconds

  motor1.run(RELEASE);    // Stop both motors
  motor2.run(RELEASE);
  delay(1000);            // Rest for 1 second

  motor1.run(BACKWARD);   // Spin both motors backward
  motor2.run(BACKWARD);
  delay(2000);

  motor1.run(RELEASE);    // Stop again
  motor2.run(RELEASE);
  delay(1000);
}
