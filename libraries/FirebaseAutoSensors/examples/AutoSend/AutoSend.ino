// Example with GPS (TinyGPS++) and pushbutton
// Requires: TinyGPSPlus library (install via Library Manager)

#include <WiFi.h>
#include <FirebaseAutoSensors.h>
#include <TinyGPSPlus.h>

// Replace with your WiFi and Firebase settings
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
const String firebaseHost = "your-project.firebaseio.com"; // without https://
const String firebaseAuth = "YOUR_DATABASE_SECRET_OR_ID_TOKEN";

FirebaseAutoSensors fas;

// Sensors
AnalogSensor *soilSensor;
DigitalSensor *buttonSensor;

TinyGPSPlus gps;

class GPSSensor : public SensorBase {
public:
  GPSSensor(const String &sid, TinyGPSPlus *g) : _id(sid), _gps(g) {}
  String id() override { return _id; }
  String readValue() override {
    if (!_gps->location.isValid()) return String("null");
    String s = "{";
    s += "\"lat\":" + String(_gps->location.lat(), 6);
    s += ",\"lon\":" + String(_gps->location.lng(), 6);
    s += "}";
    return s;
  }
private:
  String _id;
  TinyGPSPlus* _gps;
};

GPSSensor *gpsSensor;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  fas.begin(firebaseHost, firebaseAuth, 5000);

  soilSensor = new AnalogSensor("soil1", A0, 1.0);
  fas.addSensor(soilSensor);

  // Button on pin 2 (use INPUT_PULLUP)
  buttonSensor = new DigitalSensor("btn1", 2, true, true);
  fas.addSensor(buttonSensor);

  // GPS: wire GPS TX->RX1, RX->TX1 and use Serial1 (ESP32) or adjust accordingly
  #if defined(ESP32)
    Serial1.begin(9600, SERIAL_8N1, 16, 17); // RX=16, TX=17 as example
  #else
    Serial1.begin(9600);
  #endif

  gpsSensor = new GPSSensor("gps1", &gps);
  fas.addSensor(gpsSensor);
}

void loop() {
  while (Serial1.available()) {
    gps.encode(Serial1.read());
  }
  fas.loop();
}
