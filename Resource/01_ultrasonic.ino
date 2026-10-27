/*
  01 - Ultrasonic Sensor (HC-SR04)
  Board: Arduino Uno / Nano
  Libraries required: NONE (uses only built-in Arduino functions)

  Wiring:
    VCC  -> 5V
    GND  -> GND
    TRIG -> D9
    ECHO -> D10
*/

const int trigPin = 9;    // Pin that sends the sound pulse
const int echoPin = 10;   // Pin that receives the echo

void setup() {
  Serial.begin(9600);         // Start the Serial Monitor at 9600 baud
  pinMode(trigPin, OUTPUT);   // Trig sends a signal, so it is an OUTPUT
  pinMode(echoPin, INPUT);    // Echo listens for a signal, so it is an INPUT
}

void loop() {
  digitalWrite(trigPin, LOW);    // Make sure the trigger is off
  delayMicroseconds(2);          // Wait 2 microseconds
  digitalWrite(trigPin, HIGH);   // Send a pulse...
  delayMicroseconds(10);         // ...that lasts 10 microseconds
  digitalWrite(trigPin, LOW);    // Turn the trigger off again

  // Measure how long (in microseconds) the echo pin stays HIGH.
  // 30000 is a timeout so the code never gets stuck if nothing is in range.
  long duration = pulseIn(echoPin, HIGH, 30000);
  float distance = duration * 0.0343 / 2;

  delay(500);   // Wait half a second before the next reading
}
