/*
  02 - IR Obstacle Sensor (3-pin module)
  Board: Arduino Uno / Nano
  Libraries required: NONE (uses only built-in Arduino functions)

  Wiring:
    VCC -> 5V
    GND -> GND
    OUT -> D2

  Tip: Turn the small blue potentiometer on the module to change the range.
*/

const int irPin = 2;   // Pin connected to the sensor OUT pin

void setup() {
  Serial.begin(9600);      // Start the Serial Monitor at 9600 baud
  pinMode(irPin, INPUT);   // The sensor sends a signal to us, so INPUT
}

void loop() {
  int state = digitalRead(irPin);   // Read the sensor: HIGH or LOW

  // Most IR modules output LOW when an object is detected.
  if (state == LOW) {
    Serial.println("Object detected");
  } else {
    Serial.println("No object");
  }

  delay(300);   // Small pause so the Serial Monitor is readable
}
