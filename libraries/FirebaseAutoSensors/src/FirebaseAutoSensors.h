#pragma once

#include <Arduino.h>
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif
#include <vector>

class SensorBase {
public:
  virtual String id() = 0;
  virtual String readValue() = 0; // return stringified value
  virtual ~SensorBase() {}
};

class FirebaseAutoSensors {
public:
  FirebaseAutoSensors();
  void begin(const String &host, const String &auth, unsigned long intervalMs = 5000);
  void addSensor(SensorBase *sensor);
  void loop();

private:
  String _host;
  String _auth;
  unsigned long _intervalMs;
  unsigned long _lastMs;
  std::vector<SensorBase *> _sensors;
  void pushAll();
};

// Helper: a simple sensor adapter for analog pins
class AnalogSensor : public SensorBase {
public:
  AnalogSensor(const String &sensorId, uint8_t pin, float scale = 1.0);
  String id() override;
  String readValue() override;
private:
  String _id;
  uint8_t _pin;
  float _scale;
};
