/*
  04 - BMP280 Pressure and Temperature Sensor (I2C)
  Board: Arduino Uno / Nano

  Libraries required (install from Sketch > Include Library > Manage Libraries):
    - "Adafruit BMP280 Library" by Adafruit ... version 2.6.8
    - "Adafruit BusIO" by Adafruit ............ version 1.16.1
    - "Adafruit Unified Sensor" by Adafruit ... version 1.1.14
  (If the IDE asks to install dependencies, click "Install all".)

  Wiring (Uno / Nano):
    VCC -> 3.3V (or 5V if your board has a regulator, check the label)
    GND -> GND
    SDA -> A4
    SCL -> A5

  The I2C address is usually 0x76 or 0x77. If the sensor is not found,
  change 0x76 to 0x77 below.
*/

#include <Wire.h>              // Library for I2C communication
#include <Adafruit_BMP280.h>   // Library for the BMP280 sensor

Adafruit_BMP280 bmp;   // Create the sensor object

void setup() {
  Serial.begin(9600);   // Start the Serial Monitor at 9600 baud

  // Try to start the sensor at address 0x76
  if (!bmp.begin(0x76)) {
    Serial.println("BMP280 not found. Check wiring or try address 0x77.");
    while (true);   // Stop here forever
  }
}

void loop() {
  float temperature = bmp.readTemperature();          // Temperature in Celsius
  float pressure = bmp.readPressure() / 100.0;        // Pa -> hPa
  float altitude = bmp.readAltitude(1013.25);         // Estimated height in meters

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" C   Pressure: ");
  Serial.print(pressure);
  Serial.print(" hPa   Altitude: ");
  Serial.print(altitude);
  Serial.println(" m");

  delay(1000);   // Read once per second
}
