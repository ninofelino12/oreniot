#include <WiFi.h>
#include <FirebaseAutoSensors.h>

// Replace with your WiFi and Firebase settings
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
const String firebaseHost = "your-project.firebaseio.com"; // without https://
const String firebaseAuth = "YOUR_DATABASE_SECRET_OR_ID_TOKEN";

FirebaseAutoSensors fas;

// Example: create sensors and add them to library
AnalogSensor *s1;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  fas.begin(firebaseHost, firebaseAuth, 5000);

  s1 = new AnalogSensor("soil1", A0, 1.0);
  fas.addSensor(s1);
}

void loop() {
  fas.loop();
}
