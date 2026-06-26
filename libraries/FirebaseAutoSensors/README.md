# FirebaseAutoSensors

Library to auto-register sensors and push their values to Firebase Realtime Database using REST API.

Usage
- Place the `FirebaseAutoSensors` folder into Arduino `libraries` directory or use library manager.
- Include `<FirebaseAutoSensors.h>` in your sketch.
- Call `begin(host, auth, intervalMs)` and add sensors using `addSensor()`.

Example
See `examples/AutoSend/AutoSend.ino`.

Notes
- Designed for ESP8266/ESP32 using `WiFiClientSecure` and HTTPS.
- For production, replace `setInsecure()` with proper certificate validation.
