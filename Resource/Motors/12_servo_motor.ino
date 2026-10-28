/*
  12 - Control ONE Servo Motor
  Works with: Arduino alone (no driver) OR the Adafruit L293D Motor Shield (V1)
  Board: Arduino Uno

  Libraries required:
    - "Servo" (built into the Arduino IDE, nothing to install)

  The code is the same for both setups, only the wiring differs.

  Wiring, Arduino only (no driver):
    Brown/Black wire   -> GND
    Red wire           -> 5V
    Orange/Yellow wire -> D9

  Note: One small servo (SG90 / MG90S) can run from the Arduino 5V pin.
  For larger servos, use a separate supply and join its GND to the Arduino GND.
*/

#include <Servo.h>   // Library that controls servo motors

const int servoPin = 9;   // Pin that sends the signal to the servo

Servo myServo;   // Create a servo object(name of the servo)

void setup() {
  myServo.attach(servoPin);   // Tell the library which pin the servo is on
}

void loop() {
  myServo.write(0);     // Go to 0 degrees
  delay(1000);          // Wait 1 second so the servo can reach it

  myServo.write(90);    // Go to 90 degrees (middle)
  delay(1000);

  myServo.write(180);   // Go to 180 degrees
  delay(1000);
}
