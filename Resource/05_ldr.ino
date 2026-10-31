/*
  05 - LDR (Light Dependent Resistor)
  Board: Arduino Uno / Nano
  Libraries required: NONE (uses only built-in Arduino functions)

  Wiring (voltage divider with a 10k resistor):
    5V -> LDR -> A0 -> 10k resistor -> GND
  (A0 connects to the point between the LDR and the resistor.)

  Result: brighter light = bigger number (0 to 1023).
*/

const int ldrPin = A0;   // Analog pin that reads the LDR

void setup() {
  Serial.begin(9600);   // Start the Serial Monitor at 9600 baud
}

void loop() {
  int light = analogRead(ldrPin);   // Read a value from 0 (dark) to 1023 (bright)

  Serial.print("Light level: ");
  Serial.print(light);

  if (light < 300) {
    Serial.println("  -> Dark");
  } else if (light < 700) {
    Serial.println("  -> Normal");
  } else {
    Serial.println("  -> Bright");
  }

  delay(500);   // Wait half a second between readings
}
