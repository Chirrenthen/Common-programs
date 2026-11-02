/*
  09 - Adafruit Motor Driver Shield (V1): motors + servo together
  Board: Arduino Uno

  Libraries required:
    - "Adafruit Motor Shield library" (V1, AFMotor.h) ... version 1.0.1
    - "Servo" (built into the Arduino IDE)

  What this shows:
    - One BO motor on M3
    - One servo on the shield's SERVO_2 header (this header uses pin 9)
    (The SERVO_1 header uses pin 10.)

  Power: connect an external 4.5V to 12V supply to the EXT_PWR terminal.
*/

#include <AFMotor.h>   // Library for the V1 motor shield
#include <Servo.h>     // Library for the servo

AF_DCMotor motor(3);   // Motor connected to the M3 terminal
Servo myServo;         // Create a servo object

void setup() {
  Serial.begin(9600);     // Start the Serial Monitor at 9600 baud
  myServo.attach(9);      // SERVO_2 header is wired to pin 9
  motor.setSpeed(180);    // Motor speed from 0 to 255
  Serial.println("Shield test started");
}

void loop() {
  Serial.println("Motor forward, servo at 0");
  myServo.write(0);       // Turn the servo to 0 degrees
  motor.run(FORWARD);     // Start the motor forward
  delay(2000);

  Serial.println("Motor stop, servo at 90");
  myServo.write(90);      // Turn the servo to 90 degrees
  motor.run(RELEASE);     // Stop the motor
  delay(1000);

  Serial.println("Motor backward, servo at 180");
  myServo.write(180);     // Turn the servo to 180 degrees
  motor.run(BACKWARD);    // Run the motor backward
  delay(2000);

  Serial.println("Motor stop, servo at 90");
  myServo.write(90);
  motor.run(RELEASE);
  delay(1000);
}
