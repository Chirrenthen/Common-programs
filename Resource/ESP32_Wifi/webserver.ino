#include <WiFi.h>
#include <WebServer.h>

// Set your Access Point credentials
const char* ap_ssid = "ESP32_Control";
const char* ap_password = "password"; // Must be at least 8 characters

// Define the built-in LED pin (Most ESP32 boards use GPIO 2)
const int ledPin = 2;
bool ledState = false;

// Create a web server object on port 80
WebServer server(80);

// HTML, CSS, and JS page layout
String getHTML() {
  const char* statusClass = ledState ? "on" : "off";
  const char* statusText = ledState ? "ON" : "OFF";

  String html = R"HTML(<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="icon" href="data:,">
    <title>ESP32 Control Hub</title>
    <style>
      body {
        background-color: #f4f4f9;
        color: #333;
        font-family: Arial, sans-serif;
        margin: 0 auto;
        padding-top: 50px;
        text-align: center;
      }

      .container {
        background: white;
        border-radius: 12px;
        box-shadow: 0 4px 15px rgba(0, 0, 0, 0.1);
        margin: 0 auto;
        max-width: 400px;
        padding: 30px;
      }

      h1 {
        color: #4A90E2;
        margin-bottom: 5px;
      }

      p {
        color: #666;
        font-size: 18px;
      }

      .status {
        border-radius: 4px;
        font-weight: bold;
        padding: 5px 10px;
      }

      .on {
        background-color: #e6f4ea;
        color: #137333;
      }

      .off {
        background-color: #fce8e6;
        color: #c5221f;
      }

      .button {
        background-color: #4A90E2;
        border-radius: 8px;
        color: white;
        display: inline-block;
        font-size: 20px;
        font-weight: bold;
        margin: 25px 0;
        padding: 16px 40px;
        text-decoration: none;
        transition: background-color 0.3s ease;
      }

      .button:hover {
        background-color: #357ABD;
      }

      .button:active {
        background-color: #2A6096;
      }
    </style>
  </head>
  <body>
    <main class="container">
      <h1>ESP32 Control Hub</h1>
      <p>
        Device Status:
        <span class="status )HTML";
  html += statusClass;
  html += R"HTML(">)HTML";
  html += statusText;
  html += R"HTML(</span>
      </p>
      <a class="button" href="/toggle">Toggle LED</a>
    </main>
  </body>
</html>)HTML";

  return html;
}

// Handler for the root URL (http://192.168.4)
void handleRoot() {
  server.send(200, "text/html", getHTML());
}

// Handler for when the button is pressed (http://192.168.4toggle)
void handleToggle() {
  ledState = !ledState;
  digitalWrite(ledPin, ledState ? HIGH : LOW);
  
  // Redirect back to the root page to display updated status immediately
  server.sendHeader("Location", "/");
  server.send(303); 
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Start with LED off

  Serial.println("\nInitializing Access Point...");
  if (WiFi.softAP(ap_ssid, ap_password)) {
    Serial.println("Access Point ready!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP());
  } else {
    Serial.println("AP Configuration Failed.");
  }

  // Define server routing URLs
  server.on("/", handleRoot);
  server.on("/toggle", handleToggle);

  // Start the server
  server.begin();
  Serial.println("HTTP Web Server started.");
}

void loop() {
  // Listen for incoming client connections (like requests from your browser)
  server.handleClient();
}
