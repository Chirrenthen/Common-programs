/*
  06 - MPU6050 Accelerometer and Gyroscope (I2C)
  Board: Arduino Uno / Nano

  Libraries required (install from Sketch > Include Library > Manage Libraries):
    - "Adafruit MPU6050" by Adafruit .......... version 2.2.6
    - "Adafruit BusIO" by Adafruit ............ version 1.16.1
    - "Adafruit Unified Sensor" by Adafruit ... version 1.1.14
  (If the IDE asks to install dependencies, click "Install all".)

  Wiring (Uno / Nano):
    VCC -> 5V (3.3V also works on most GY-521 boards)
    GND -> GND
    SDA -> A4
    SCL -> A5
*/

#include <Wire.h>               // Library for I2C communication
#include <Adafruit_MPU6050.h>   // Library for the MPU6050 sensor
#include <Adafruit_Sensor.h>    // Gives us the sensors_event_t data type

Adafruit_MPU6050 mpu;   // Create the sensor object

void setup() {
  Serial.begin(9600);   // Start the Serial Monitor at 9600 baud

  if (!mpu.begin()) {   // Try to start the sensor
    Serial.println("MPU6050 not found. Check wiring.");
    while (true);       // Stop here forever
  }
}

void loop() {
  sensors_event_t accel, gyro, temp;      // Boxes to hold the readings
  mpu.getEvent(&accel, &gyro, &temp);     // Fill the boxes with fresh data

  Serial.print("Accel X: ");
  Serial.print(accel.acceleration.x);     // Acceleration in m/s^2
  Serial.print("  Y: ");
  Serial.print(accel.acceleration.y);
  Serial.print("  Z: ");
  Serial.println(accel.acceleration.z);

  Serial.print("Gyro  X: ");
  Serial.print(gyro.gyro.x);              // Rotation speed in rad/s
  Serial.print("  Y: ");
  Serial.print(gyro.gyro.y);
  Serial.print("  Z: ");
  Serial.println(gyro.gyro.z);

  Serial.print("Temp: ");
  Serial.print(temp.temperature);         // Chip temperature in Celsius
  Serial.println(" C");
  Serial.println();

  delay(500);   // Wait half a second between readings
}
