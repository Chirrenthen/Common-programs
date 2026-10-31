#include <WiFi.h>
#include <WebServer.h>

// 1. Define your custom hotspot credentials (No internet required)
const char* ap_ssid     = "ESP32";
const char* ap_password = "1234"; // Must be at least 8 characters

// 2. Initialize the web server on Port 80
WebServer server(80);

const int in1 = 32; 
const int in2 = 33; 

const int in3 = 26; 
const int in4 = 25;

void moveForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  Serial.println("Direction: FORWARD");
}

void moveBackward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  Serial.println("Direction: BACKWARD");
}

void turnLeft() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  Serial.println("Direction: LEFT");
}

void turnRight() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  Serial.println("Direction: RIGHT");
}

void stopRobot() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  Serial.println("Direction: STOPPED");
}


// HTML layout arranged as a clean, thumb-friendly D-Pad controller layout
String getHTMLPage() {
  return String(R"HTML(<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
  <title>Robot Control Panel</title>
  <style>
    html {
      font-family: Helvetica, sans-serif;
      text-align: center;
      background-color: #2c3e50;
      color: white;
      user-select: none;
    }

    h1 {
      margin-top: 20px;
      font-size: 26px;
    }

    .dpad-container {
      display: grid;
      grid-template-columns: repeat(3, 100px);
      grid-template-rows: repeat(3, 100px);
      gap: 10px;
      justify-content: center;
      margin: 40px auto 20px;
    }

    .btn {
      display: flex;
      align-items: center;
      justify-content: center;
      font-size: 18px;
      font-weight: bold;
      color: white;
      text-decoration: none;
      border-radius: 12px;
      box-shadow: 0 4px #1a252f;
      transition: all 0.1s;
    }

    .btn:active {
      transform: translateY(4px);
      box-shadow: 0 0 #1a252f;
    }

    .drive {
      background-color: #3498db;
    }

    .stop {
      background-color: #e74c3c;
      grid-column: 2;
      grid-row: 2;
    }

    .forward {
      grid-column: 2;
      grid-row: 1;
    }

    .left {
      grid-column: 1;
      grid-row: 2;
    }

    .right {
      grid-column: 3;
      grid-row: 2;
    }

    .backward {
      grid-column: 2;
      grid-row: 3;
    }
  </style>
</head>
<body>
  <h1>Robot Control Panel</h1>
  <p>IP: 192.168.4.1</p>

  <div class="dpad-container">
    <a href="/forward" class="btn drive forward">Fw<br>Forward</a>
    <a href="/left" class="btn drive left">L<br>Left</a>
    <a href="/stop" class="btn stop">STOP</a>
    <a href="/right" class="btn drive right">Right<br>R</a>
    <a href="/backward" class="btn drive backward">Backward<br>Bw</a>
  </div>
</body>
</html>)HTML");
}

// HTTP Route Handlers
void handleRoot() {
  server.send(200, "text/html", getHTMLPage());
}

void handleForward() {
  moveForward();
  server.send(200, "text/html", getHTMLPage());
}

void handleBackward() {
  moveBackward();
  server.send(200, "text/html", getHTMLPage());
}

void handleLeft() {
  turnLeft();
  server.send(200, "text/html", getHTMLPage());
}

void handleRight() {
  turnRight();
  server.send(200, "text/html", getHTMLPage());
}

void handleStop() {
  stopRobot();
  server.send(200, "text/html", getHTMLPage());
}

void setup() {
  Serial.begin(115200);
  
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Make sure hardware boots into a stopped state
  stopRobot(); 

  // Set Up ap
  Serial.print("\n AP starting..");
  WiFi.softAP(ap_ssid, ap_password);

  IPAddress IP = WiFi.softAPIP();
  Serial.println("Ready");
  Serial.print("Connected to: ");
  Serial.println(ap_ssid);
  Serial.print("Open http://");
  Serial.println(IP);

  // Map endpoints to directional functions
  server.on("/", handleRoot);
  server.on("/forward", handleForward);
  server.on("/backward", handleBackward);
  server.on("/left", handleLeft);
  server.on("/right", handleRight);
  server.on("/stop", handleStop);

  server.begin();
  Serial.println("HTTP started");
}

void loop() {
  server.handleClient();
}
