#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Define the DHT11 sensor
#define DHTPIN 3     // Pin where the DHT11 is connected
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// Initialize the LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Start the serial communication
  Serial.begin(9600);
  
  // Initialize the DHT11 sensor
  dht.begin();
  
  // Initialize the LCD
  lcd.init();
  lcd.backlight();
}

void loop() {
  // Read humidity and temperature
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Print the data to the Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");

  // Print the data to the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperature: ");
  lcd.print(temperature);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print(" %");
  
  // Wait a few seconds between measurements.
  delay(2000);
}
