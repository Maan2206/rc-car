#include <WiFi.h>
#include <WebServer.h>

// WiFi credentials
const char* ssid = "ESP32-Car";  // an
const char* password = "12345678";  // riya@6290

// Motor pins
int motor1Pin1 = 32;
int motor1Pin2 = 33;
int motor2Pin1 = 25;
int motor2Pin2 = 26;

WebServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  stopMotors();  // Ensures motors are stopped initially

  WiFi.softAP(ssid, password);  // Start the Wi-Fi access point
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/", HTTP_GET, handleRoot);
  server.on("/forward", HTTP_GET, handleForward);
  server.on("/backward", HTTP_GET, handleBackward);
  server.on("/left", HTTP_GET, handleLeft);
  server.on("/right", HTTP_GET, handleRight);
  server.on("/stop", HTTP_GET, handleStop);
  
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String html = "<html><head><title>ESP32 RC Car</title></head><body><h1>Control the RC Car</h1><button onclick=\"window.location.href='/forward'\">Forward</button><button onclick=\"window.location.href='/backward'\">Backward</button><button onclick=\"window.location.href='/left'\">Left</button><button onclick=\"window.location.href='/right'\">Right</button><button onclick=\"window.location.href='/stop'\">Stop</button></body></html>";
  server.send(200, "text/html", html);
}

void handleForward() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  server.send(200, "text/plain", "Moving Forward");
}

void handleBackward() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  server.send(200, "text/plain", "Moving Backward");
}

void handleLeft() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  server.send(200, "text/plain", "Turning Left");
}

void handleRight() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  server.send(200, "text/plain", "Turning Right");
}

void handleStop() {
  stopMotors();
  server.send(200, "text/plain", "Stopped");
}

void stopMotors() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}
