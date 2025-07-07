**ESP8266 Wi-Fi Smart Switch with SinricPro**

This project showcases a Wi-Fi-enabled smart switch system built around the ESP8266 microcontroller and seamlessly integrated with the SinricPro IoT platform. It allows you to control an LED—or any connected appliance—both remotely via the internet and locally using a physical button.

The system demonstrates how to merge hardware and cloud technologies, enabling real-time updates and synchronization between manual operations and remote commands from apps or voice assistants like Alexa and Google Home.

Designed for smart home applications, this project is a practical example of how IoT solutions can bring convenience, flexibility, and modern automation into everyday life.

**Features**

Connects to a Wi-Fi network and maintains the connection.
Controls an LED (or any load) via:
SinricPro app/voice assistant (Alexa, Google Home, etc.)
Physical tactile switch
Sends state updates back to SinricPro when toggled manually.
Displays Wi-Fi status via a dedicated LED.

**Hardware Connections**

| Function                       | ESP8266 Pin | GPIO | Description                       |
| ------------------------------ | ----------- | ---- | --------------------------------- |
| Main LED                       | D1          | 5    | The LED controlled via app/switch |
| Tactile Button (manual toggle) | SD3         | 10   | Physical button for LED control   |
| Wi-Fi Status LED               | D0          | 16   | Shows Wi-Fi connection status     |


**Libraries Used**

ESP8266WiFi.h → manages Wi-Fi connection
SinricPro.h, SinricProSwitch.h → connects to SinricPro platform
Arduino.h → core Arduino functions
map → stores dynamic mappings between device IDs and hardware pins

**Practical Applications**

Smart home lighting
Remote appliance control
Voice-activated devices with Alexa/Google Home
IoT learning projects
