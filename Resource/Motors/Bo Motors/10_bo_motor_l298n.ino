/*
  10 - Control ONE BO Motor with an L298N driver module
  Board: Arduino Uno

  Libraries required: NONE (uses only built-in Arduino functions)

  Wiring:
    Motor wires  -> OUT1 and OUT2
    ENA          -> D9 (remove the ENA jumper cap first)
    IN1          -> D8
    IN2          -> D7
    12V terminal -> battery +   (6V to 12V, matching your motor)
    GND terminal -> battery -   AND Arduino GND (must be shared)

  If the motor spins the wrong way, swap its two wires.
*/

const int enPin = 9;    // Speed pin (must be a PWM pin)
const int in1Pin = 8;   // Direction pin 1
const int in2Pin = 7;   // Direction pin 2

const int motorSpeed = 200;   // Speed from 0 (stop) to 255 (full speed)

void setup() {
  pinMode(enPin, OUTPUT);    // All three pins send signals out to the driver
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  analogWrite(enPin, motorSpeed);   // PWM on ENA sets the motor speed
}

void loop() {
  digitalWrite(in1Pin, HIGH);   // IN1 HIGH + IN2 LOW = forward
  digitalWrite(in2Pin, LOW);
  delay(2000);                  // Run for 2 seconds

  digitalWrite(in1Pin, LOW);    // Both LOW = stop
  digitalWrite(in2Pin, LOW);
  delay(1000);                  // Rest for 1 second

  digitalWrite(in1Pin, LOW);    // IN1 LOW + IN2 HIGH = backward
  digitalWrite(in2Pin, HIGH);
  delay(2000);                  // Run for 2 seconds

  digitalWrite(in1Pin, LOW);    // Stop again
  digitalWrite(in2Pin, LOW);
  delay(1000);                  // Rest for 1 second
}
