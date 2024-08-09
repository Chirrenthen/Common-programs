const int potPin = A0; // Potentiometer connected to analog pin A0
const int ledPin = 6;  // LED connected to digital pin 6

int potValue = 0;      // Variable to store the potentiometer reading
int brightness = 0;   // Variable to store the LED brightness value

void setup() {
  pinMode(ledPin, OUTPUT);  // Set LED pin as output
  Serial.begin(9600);       // Optional: Initialize serial communication for debugging
}

void loop() {
  potValue = analogRead(potPin);  // Read the analog value from the potentiometer

  // Option 1: Simpler scaling with range check (adjust divisor as needed)
  brightness = potValue / 16;
  brightness = constrain(brightness, 0, 255); // Limit brightness to 0-255 range

  // Option 2: Using map() function for precise control
  // brightness = map(potValue, 0, 1023, 0, 255);

  // Optional: Print potentiometer value for debugging
  Serial.print("Potentiometer Value: ");
  Serial.println(potValue);

  analogWrite(ledPin, brightness);  // Send the brightness value to the LED
}



