/*
  03 - DHT11 Temperature and Humidity Sensor
  Board: Arduino Uno / Nano

  Libraries required (install from Sketch > Include Library > Manage Libraries):
    - "DHT sensor library" by Adafruit ........ version 1.4.6
    - "Adafruit Unified Sensor" by Adafruit ... version 1.1.14
  (If the IDE asks to install dependencies, click "Install all".)

  Wiring (3-pin module):
    VCC -> 5V
    GND -> GND
    DATA/OUT -> D2
  Bare 4-pin sensor: add a 10k resistor between VCC and DATA.
*/

#include <DHT.h>   // Library that talks to the DHT sensor

#define DHTPIN 2        // Data pin is connected to D2
#define DHTTYPE DHT11   // We are using the DHT11 model

DHT dht(DHTPIN, DHTTYPE);   // Create the sensor object

void setup() {
  Serial.begin(9600);   // Start the Serial Monitor at 9600 baud
  dht.begin();          // Start the sensor
}

void loop() {
  delay(2000);   // DHT11 is slow: it can only be read once every 2 seconds

  float humidity = dht.readHumidity();          // Read humidity in %
  float temperature = dht.readTemperature();    // Read temperature in Celsius

  // isnan = "is not a number". It is true when the read failed.
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT11. Check wiring.");
    return;   // Skip the rest and try again
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" C   Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
}
