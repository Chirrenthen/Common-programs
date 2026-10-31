1. ### Ultrasonic sensor — Measures distance. 
It sends a brief ultrasonic pulse and measures how long the echo takes to return after bouncing off an object. 
The distance is estimated from this round-trip time, so soft surfaces or angled targets can affect the reading.

2. ### IR sensor — Detects nearby objects or infrared light.
An emitter sends infrared light, while a receiver detects reflected light or changes in IR intensity. 
Reflective IR sensors are often used for short-range object detection or line following; readings can vary with distance, surface color, and ambient light.

3. ### DHT11 — Measures temperature and humidity. 
Its sensing elements detect temperature and relative humidity, and built-in electronics convert them into digital readings. 
It is inexpensive and simple to connect, though its range, resolution, and update rate are limited compared with more advanced sensors.

4. ### BMP280 — Measures air pressure and temperature. 
MEMS sensing elements measure atmospheric pressure and temperature, then provide digital readings over I²C or SPI. 
Pressure readings can be used to estimate altitude, but weather changes and calibration affect that estimate.

5. ### LDR — Detects light intensity. 
Its electrical resistance generally decreases as the light falling on it increases. 
It is commonly used in a voltage-divider circuit so a microcontroller can read a changing voltage; it is useful for basic light-level detection but is relatively slow and not highly precise.

6. ### MPU6050 — Measures acceleration and rotation. 
Its three-axis accelerometer measures linear acceleration, and its three-axis gyroscope measures angular rotation.
It sends readings over I²C; combining the data can help estimate orientation, though drift and calibration should be considered.

7. ### Servo motor — Not a sensor; it moves to a commanded angle. 
A control signal, typically a repeating pulse whose width represents the target position, commands the shaft angle. 
Internal feedback helps the servo move toward and hold that position; its rotation range, torque, and speed depend on the model.

8. ### BO motors — Small geared DC motors commonly used in robots. 
These small geared DC motors commonly drive robot wheels. 
Applying voltage turns the motor, and reversing polarity reverses its direction; speed can be adjusted with pulse-width modulation (PWM), usually through a motor driver.
