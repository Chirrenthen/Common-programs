const int lineSensorPin = 34; // Analog input pin for line sensor (D34)
const int threshold = 1000;   // Adjust this value based on your sensor and environment

void setup() {
  Serial.begin(115200);
}

void loop() {
  int sensorValue = analogRead(lineSensorPin);
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);

  if (sensorValue < threshold) {
    Serial.println("Line detected");
  } else {
    Serial.println("No line detected");
  }

  delay(100); // Wait 100 ms before taking another reading
}
