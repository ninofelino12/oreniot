# FirebaseAutoSensors

![Release](https://img.shields.io/github/v/release/ninofelino12/oreniot?label=FirebaseAutoSensors%20v&style=flat-square)

Library to auto-register sensors and push their values to Firebase Realtime Database using REST API.

Installation

- Option A — Manual install (recommended):
  1. Copy the `FirebaseAutoSensors` folder into your Arduino libraries folder (usually `~/Arduino/libraries/`).
 2. Restart Arduino IDE.

- Option B — Add ZIP in Arduino IDE:
  1. From repository root, create a ZIP: `zip -r FirebaseAutoSensors.zip FirebaseAutoSensors`.
 2. In Arduino IDE: Sketch → Include Library → Add .ZIP Library and select the ZIP.

Usage
- Include `<FirebaseAutoSensors.h>` in your sketch.
- Call `begin(host, auth, intervalMs)` and add sensors using `addSensor()`.

Example
See `examples/AutoSend/AutoSend.ino`.

Notes
- Designed for ESP8266/ESP32 using `WiFiClientSecure` and HTTPS.
- For production, replace `setInsecure()` with proper certificate validation.
