#include "FirebaseAutoSensors.h"
#include <WiFiClientSecure.h>
#if defined(ESP8266)
#include <ESP8266HTTPClient.h>
#else
#include <HTTPClient.h>
#endif

FirebaseAutoSensors::FirebaseAutoSensors()
  : _host(""), _auth(""), _intervalMs(5000), _lastMs(0) {}

void FirebaseAutoSensors::begin(const String &host, const String &auth, unsigned long intervalMs) {
  _host = host;
  _auth = auth;
  _intervalMs = intervalMs;
  _lastMs = millis();
}

void FirebaseAutoSensors::addSensor(SensorBase *sensor) {
  _sensors.push_back(sensor);
}

void FirebaseAutoSensors::loop() {
  unsigned long now = millis();
  if (now - _lastMs >= _intervalMs) {
    _lastMs = now;
    pushAll();
  }
}

void FirebaseAutoSensors::pushAll() {
  if (_host.length() == 0) return;
  for (auto s : _sensors) {
    String path = "/sensors/" + s->id() + ".json";
    String url = String("https://") + _host + path + "?auth=" + _auth;

    String payload = s->readValue();

    HTTPClient http;
    WiFiClientSecure *client = new WiFiClientSecure();
    client->setInsecure();
    http.begin(*client, url);
    http.addHeader("Content-Type", "application/json");
    int code = http.PUT(payload);
    http.end();
    delete client;
  }
}

AnalogSensor::AnalogSensor(const String &sensorId, uint8_t pin, float scale)
  : _id(sensorId), _pin(pin), _scale(scale) {
}

String AnalogSensor::id() { return _id; }

String AnalogSensor::readValue() {
  int raw = analogRead(_pin);
  float v = raw * _scale;
  return String(v);
}

DigitalSensor::DigitalSensor(const String &sensorId, uint8_t pin, bool pullup, bool invert)
  : _id(sensorId), _pin(pin), _invert(invert) {
  pinMode(_pin, pullup ? INPUT_PULLUP : INPUT);
}

String DigitalSensor::id() { return _id; }

String DigitalSensor::readValue() {
  int v = digitalRead(_pin);
  bool val = _invert ? !v : v;
  return val ? String("true") : String("false");
}
