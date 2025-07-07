#define ENABLE_DEBUG

#ifdef ENABLE_DEBUG
  #define DEBUG_ESP_PORT Serial
  #define NODEBUG_WEBSOCKETS
  #define NDEBUG
#endif

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "SinricPro.h"
#include "SinricProSwitch.h"

#include <map>

#define WIFI_SSID     "motorola edge 40 neo"    
#define WIFI_PASS     "Prabhat@0717"
#define APP_KEY       "02ecb3b5-28ee-4b16-acab-6f2acc4790c3"
#define APP_SECRET    "7fa6f762-58bf-4154-adb3-a753d7fb7017-26fe6635-0bd1-418b-a07c-4daa59acda4b"

// Your SinricPro device ID
#define device_ID_1   "6868ab166868ee0e88a56d93"

// define the GPIO connected with LEDs and switches
#define LedPin1      5    // D1 → LED
#define SwitchPin1   10   // SD3 → Button
#define wifiLed      16   // D0 → WiFi status LED

#define TACTILE_BUTTON 1
#define BAUD_RATE       9600
#define DEBOUNCE_TIME   250

typedef struct {
  int ledPIN;
  int flipSwitchPIN;
} deviceConfig_t;

std::map<String, deviceConfig_t> devices = {
  {device_ID_1, { LedPin1, SwitchPin1 }},
};

typedef struct {
  String deviceId;
  bool lastFlipSwitchState;
  unsigned long lastFlipSwitchChange;
} flipSwitchConfig_t;

std::map<int, flipSwitchConfig_t> flipSwitches;

void setupLEDs() {
  for (auto &device : devices) {
    int ledPIN = device.second.ledPIN;
    pinMode(ledPIN, OUTPUT);
    digitalWrite(ledPIN, LOW); // LED OFF initially for active HIGH
  }
}

void setupFlipSwitches() {
  for (auto &device : devices) {
    flipSwitchConfig_t flipSwitchConfig;
    flipSwitchConfig.deviceId = device.first;
    flipSwitchConfig.lastFlipSwitchChange = 0;
    flipSwitchConfig.lastFlipSwitchState = true;

    int flipSwitchPIN = device.second.flipSwitchPIN;

    flipSwitches[flipSwitchPIN] = flipSwitchConfig;
    pinMode(flipSwitchPIN, INPUT_PULLUP);
  }
}

bool onPowerState(String deviceId, bool &state) {
  Serial.printf("[SinricPro] Device %s → %s\r\n", deviceId.c_str(), state ? "ON" : "OFF");
  int ledPIN = devices[deviceId].ledPIN;
  digitalWrite(ledPIN, state ? HIGH : LOW); // ✅ ACTIVE HIGH logic
  return true;
}

void handleFlipSwitches() {
  unsigned long actualMillis = millis();

  for (auto &flipSwitch : flipSwitches) {
    unsigned long lastFlipSwitchChange = flipSwitch.second.lastFlipSwitchChange;

    if (actualMillis - lastFlipSwitchChange > DEBOUNCE_TIME) {
      int flipSwitchPIN = flipSwitch.first;
      bool lastFlipSwitchState = flipSwitch.second.lastFlipSwitchState;
      bool flipSwitchState = digitalRead(flipSwitchPIN);

      if (flipSwitchState != lastFlipSwitchState) {
#ifdef TACTILE_BUTTON
        if (flipSwitchState) {
#endif
          flipSwitch.second.lastFlipSwitchChange = actualMillis;
          String deviceId = flipSwitch.second.deviceId;
          int ledPIN = devices[deviceId].ledPIN;
          
          bool newLedState = !digitalRead(ledPIN);     // toggle LED state
          digitalWrite(ledPIN, newLedState);           // write new LED state

          SinricProSwitch &mySwitch = SinricPro[deviceId];
          mySwitch.sendPowerStateEvent(newLedState == HIGH); // send true if LED ON
#ifdef TACTILE_BUTTON
        }
#endif
        flipSwitch.second.lastFlipSwitchState = flipSwitchState;
      }
    }
  }
}

void setupWiFi() {
  Serial.println("\r\n[WiFi]: Connecting to WiFi...");

  WiFi.begin(WIFI_SSID, WIFI_PASS);

  int dotCount = 0;
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(wifiLed, LOW);
    delay(200);
    digitalWrite(wifiLed, HIGH);
    delay(200);

    Serial.print(".");
    dotCount++;
    if (dotCount % 40 == 0) {
      Serial.println();
    }
  }

  digitalWrite(wifiLed, LOW); // LED ON when connected

  Serial.println("\r\n[WiFi]: Connected!");
  Serial.print("[WiFi]: SSID: ");
  Serial.println(WIFI_SSID);
  Serial.print("[WiFi]: IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("[WiFi]: Signal Strength (RSSI): ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
}

void setupSinricPro() {
  for (auto &device : devices) {
    const char *deviceId = device.first.c_str();
    SinricProSwitch &mySwitch = SinricPro[deviceId];
    mySwitch.onPowerState(onPowerState);
  }

  SinricPro.begin(APP_KEY, APP_SECRET);
  SinricPro.restoreDeviceStates(true);
}

void setup() {
  Serial.begin(BAUD_RATE);

  pinMode(wifiLed, OUTPUT);
  digitalWrite(wifiLed, HIGH); // LED OFF initially

  setupLEDs();
  setupFlipSwitches();
  setupWiFi();
  setupSinricPro();
}

void loop() {
  SinricPro.handle();
  handleFlipSwitches();

  static unsigned long lastWifiCheck = 0;
  if (millis() - lastWifiCheck > 5000) {
    lastWifiCheck = millis();

    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("[WiFi]: Still connected.");
      digitalWrite(wifiLed, LOW);
    } else {
      Serial.println("[WiFi]: Disconnected. Attempting reconnect...");
      digitalWrite(wifiLed, HIGH);
      WiFi.reconnect();
    }
  }
}
