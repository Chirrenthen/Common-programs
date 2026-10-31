/*
  06 - MPU6050 Accelerometer and Gyroscope (I2C)
  Board: Arduino Uno / Nano

  Libraries required (install from Sketch > Include Library > Manage Libraries):
    - "Adafruit MPU6050" by Adafruit .......... version 2.2.6
    - "Adafruit BusIO" by Adafruit ............ version 1.16.1
    - "Adafruit Unified Sensor" by Adafruit ... version 1.1.14
  (If the IDE asks to install dependencies, click "Install all".)

  Wiring (Uno / Nano):
    VCC -> 5V (3.3V also works on most  GY-521 boards)
    GND -> GND
    SDA -> A4
    SCL -> A5
*/
#include <AFMotor.h>
#include <Wire.h>               // Library for I2C communication
#include <Adafruit_MPU6050.h>   // Library for the MPU6050 sensor
#include <Adafruit_Sensor.h>    // Gives us the sensors_event_t data type

Adafruit_MPU6050 mpu;   // Create the sensor object

const float TILT_THRESHOLD = 10.0; 

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);

void setup() {
  Serial.begin(9600);   // Start the Serial Monitor at 9600 baud
  motor1.setSpeed(200);
  motor2.setSpeed(200);
  if (!mpu.begin()) {   // Try to start the sensor
    Serial.println("MPU6050 not found. Check wiring.");
    while (true);       // Stop here forever
  }
}

void loop() {
  sensors_event_t accel, gyro, temp;      // Boxes to hold the readings
  mpu.getEvent(&accel, &gyro, &temp);     // Fill the boxes with fresh data

  // Serial.print("Accel X: ");
  // Serial.print(accel.acceleration.x);     // Acceleration in m/s^2
  // Serial.print("  Y: ");
  // Serial.print(accel.acceleration.y);
  // Serial.print("  Z: ");
  // Serial.println(accel.acceleration.z);

  float roll_rad = atan2(accel.acceleration.y, accel.acceleration.z);
  float roll_deg = roll_rad * 180.0 / M_PI;

  /* Print the exact angle to the serial monitor */
  Serial.print("Tilt Angle: ");
  Serial.print(roll_deg);
  Serial.print("° -> State: ");

  /* Determine the state based on the angle */
  if (roll_deg > TILT_THRESHOLD) {
    Serial.println("TILTED RIGHT");
    right();
  } 
  else if (roll_deg < -TILT_THRESHOLD) {
    Serial.println("TILTED LEFT");
    left();
  } 
  else {
    Serial.println("FLAT");
  }

  delay(200); // Check 5 times a second
}

int left(){
    Serial.print("/n left");
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
    delay(5000);
}

int right(){
    Serial.print("/n right");
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
}