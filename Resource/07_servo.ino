/*
  07 - Servo Motor (SG90 / MG90S)
  Board: Arduino Uno / Nano

  Libraries required:
    - "Servo" (built into the Arduino IDE, nothing to install)

  Wiring:
    Brown/Black wire  -> GND
    Red wire          -> 5V
    Orange/Yellow wire -> D9

  Note: One small servo can run from the Arduino 5V pin.
  For several or larger servos, use a separate power supply
  and connect its GND to the Arduino GND.
*/

#include <Servo.h>   // Library that controls servo motors

Servo myServo;   // Create a servo object

void setup() {
  myServo.attach(9);   // The servo signal wire is connected to D9
}

void loop() {
  // Move from 0 to 180 degrees, one degree at a time
  for (int angle = 0; angle <= 180; angle++) {
    myServo.write(angle);   // Tell the servo to go to this angle
    delay(15);              // Give the servo time to move
  }

  // Move back from 180 to 0 degrees
  for (int angle = 180; angle >= 0; angle--) {
    myServo.write(angle);
    delay(15);
  }
}
