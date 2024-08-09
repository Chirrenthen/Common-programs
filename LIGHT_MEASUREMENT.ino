const int photoresistorPin = 35; // Analog input pin for photoresistor (D34)

void setup() {
  Serial.begin(115200);
}

void loop() {
  int lightLevel = analogRead(photoresistorPin);
  Serial.print("Light Level: ");
  Serial.println(lightLevel);
  delay(1000); // Wait 1 second before taking another reading
}
