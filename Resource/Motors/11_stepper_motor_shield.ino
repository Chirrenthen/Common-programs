/*
  11 - Control ONE Stepper Motor with the Adafruit L293D Motor Shield (V1)
  Board: Arduino Uno

  Libraries required:
    - "Adafruit Motor Shield library" (V1, AFMotor.h) version 1.0.1
      (Do NOT install the "V2" library, it is for a different shield.)

  Wiring:
    Plug the shield on the Uno.
    A 4-wire stepper uses the M1 and M2 terminals together:
      coil A -> the two M1 screws
      coil B -> the two M2 screws
    (Use a multimeter to find which wires belong to the same coil:
     two wires of one coil show a small resistance, wires from different coils show none.)
    Battery -> EXT_PWR terminal (5V to 12V).

  Note: The L293D can only give about 600mA per coil. It suits small steppers
  (28BYJ-48 bipolar mod, small NEMA 14/17 with low current). A big NEMA 17
  may run hot or weak.
*/

#include <AFMotor.h>   // Library for the V1 motor shield

// 200 = steps per full turn of the motor (a 1.8 degree stepper has 200 steps)
// 1   = the stepper is on the M1 and M2 terminals (port 1)
AF_Stepper stepper(200, 1);

void setup() {
  stepper.setSpeed(30);   // Speed in RPM (turns per minute)
}

void loop() {
  stepper.step(200, FORWARD, SINGLE);     // One full turn forward
  delay(1000);                            // Wait 1 second

  stepper.step(200, BACKWARD, SINGLE);    // One full turn backward
  delay(1000);                            // Wait 1 second

  // Other step styles you can try in place of SINGLE:
  //   DOUBLE     = more torque
  //   INTERLEAVE = twice as many steps, smoother (so use 400 steps per turn)
}
