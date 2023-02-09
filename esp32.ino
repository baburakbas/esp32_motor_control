#include <WiFi.h>
#include <WebServer.h>

// Replace with your network credentials
const char *ssid = "your_SSID";
const char *password = "your_PASSWORD";

WebServer server(80);

// Define the LED pins
const int ledPins[] = {34, 35, 32, 33};

void handleRoot() {
  String html = "<html><body><h1>ESP32 Web Server</h1><p>Press the arrow keys to control the LEDs:</p>"
                "<p><a href='/left'><<</a> <a href='/up'><</a> <a href='/down'>></a> <a href='/right'>>></a></p>"
                "</body></html>";
  server.send(200, "text/html", html);
}

void handleLeft() {
  digitalWrite(ledPins[0], HIGH);
  server.send(200, "text/plain", "LED 0 ON");
}

void handleUp() {
  digitalWrite(ledPins[1], HIGH);
  server.send(200, "text/plain", "LED 1 ON");
}

void handleDown() {
  digitalWrite(ledPins[2], HIGH);
  server.send(200, "text/plain", "LED 2 ON");
}

void handleRight() {
  digitalWrite(ledPins[3], HIGH);
  server.send(200, "text/plain", "LED 3 ON");
}

void setup() {
  // Initialize the LED pins as outputs
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Start the server
  server.on("/", handleRoot);
  server.on("/left", handleLeft);
  server.on("/up", handleUp);
  server.on("/down", handleDown);
  server.on("/right", handleRight);
  server.begin();
  Serial.println("Server started");
}

void loop() {
  server.handleClient();
}
