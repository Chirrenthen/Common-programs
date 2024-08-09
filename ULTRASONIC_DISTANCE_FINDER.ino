#define trigPin 5 // Define trigger pin for the sensor
#define echoPin 6  // Define echo pin for the sensor
#define redLEDpin 8  // Define pin for red LED
#define greenLEDpin 9  // Define pin for green LED

long duration; // Variable to store pulse duration
int distance;  // Variable to store the calculated distance

void setup() {
  pinMode(trigPin, OUTPUT);  // Set trigger pin as output
  pinMode(echoPin, INPUT);    // Set echo pin as input
  pinMode(redLEDpin, OUTPUT);  // Set red LED pin as output
  pinMode(greenLEDpin, OUTPUT); // Set green LED pin as output
  Serial.begin(9600);        // Start serial communication at 9600 baud rate
}

void loop() {
  digitalWrite(trigPin, LOW);    // Set trigger pin LOW for stability
  delayMicroseconds(2);           // Wait for 2 microseconds

  digitalWrite(trigPin, HIGH);   // Set trigger pin HIGH for 10 microseconds
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);    // Set trigger pin LOW again

  duration = pulseIn(echoPin, HIGH);  // Measure pulse duration in microseconds

  // Calculate distance in centimeters (speed of sound is 340 m/s)
  distance = duration * 0.034 / 2;

  // Control LEDs based on distance
  digitalWrite(redLEDpin, distance < 15);  // Turn on red LED if distance < 10cm
  digitalWrite(greenLEDpin, distance >= 15); // Turn on green LED if distance >= 10cm

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(100);  // Wait for 100 milliseconds before next measurement
}
//  Note:
 // This digital scale has an accuracy of +/- 5cm]