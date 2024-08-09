const int photoresistorPin = 34; // Analog input pin for photoresistor (D34)
const int transistorPin = 26;    // Digital output pin for transistor (D26)

// Define a threshold for light level
const int lightThreshold = 190;  // Adjust this value based on your measurements

void setup() {
  Serial.begin(115200);
  pinMode(transistorPin, OUTPUT);
  digitalWrite(transistorPin, LOW);
}

void loop() {
  int lightLevel = analogRead(photoresistorPin);
  Serial.print("Light Level: ");
  Serial.println(lightLevel);

  if (lightThreshold < lightLevel) {                  
    digitalWrite(transistorPin, HIGH);
    Serial.println("Light ON");
  } else {
    digitalWrite(transistorPin, LOW);
    Serial.println("Light OFF");
  }

  delay(1000); // Wait 1 second before taking another reading
}
