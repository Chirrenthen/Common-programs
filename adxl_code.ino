#include <Wire.h>               
#include <Adafruit_ADXL345_U.h> //adxl345 support
#include <Adafruit_Sensor.h>
#include <AFMotor.h>

// Sensor object (assigns a unique ID of 12345 to the sensor instance)
Adafruit_ADXL345_Unified accelSensor = Adafruit_ADXL345_Unified(12345); 

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);

const float TILT_THRESHOLD = 10.0;

void setup() {
  Serial.begin(9600);

  // Initialize the ADXL345 sensor
  if (!accelSensor.begin()) {   
    Serial.println("ADXL345 not found. Check wiring.");
    while (true);
  } else {
    Serial.print("\n Working");
  }

   motor1.setSpeed(200);
   motor2.setSpeed(200);
}

void loop() {
  sensors_event_t event;      
  accelSensor.getEvent(&event); // Reads accelerometer data into the event container

  // Note: Adafruit Unified Sensor library stores data directly in event.acceleration
  float roll_rad = atan2(event.acceleration.y, event.acceleration.z);
  float roll_deg = roll_rad * 180.0 / M_PI;

  // print angle
  Serial.print("Tilt Angle: ");
  Serial.print(roll_deg);
  Serial.print("° -> State: ");

  // determine orientation
  if (roll_deg > TILT_THRESHOLD) {
    Serial.println("TILTED RIGHT");
    //right();
  } 
  else if (roll_deg < -TILT_THRESHOLD) {
    Serial.println("TILTED LEFT");
    //left();
  } 
  else {
    Serial.println("FLAT");
  }

  delay(200);
}

int left(){
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
    delay(5000);
}

int right(){
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
    delay(5000);
}
