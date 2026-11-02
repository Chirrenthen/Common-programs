// Set esp32 as an access point and allow other devices to connect to it

#include <WiFi.h>

// Set your desired network name and password
const char* ap_ssid = "ESP32_Network";
const char* ap_password = "password123"; // Must be at least 8 characters

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\nSetting up Access Point...");

  // Start the Access Point
  // Syntax: WiFi.softAP(ssid, password, channel, hidden, max_connection)
  if (WiFi.softAP(ap_ssid, ap_password)) {
    Serial.println("Access Point successfully started!");
    
    // Default IP for ESP32 AP mode is usually 192.168.4.1
    Serial.print("AP IP Address: ");
    Serial.println(WiFi.softAPIP());
  } else {
    Serial.println("Access Point initialization failed.");
  }
}

void loop() {
  // Check how many devices are currently connected to the ESP32
  Serial.print("Stations connected: ");
  Serial.println(WiFi.softAPgetStationNum());
  delay(5000); 
}
