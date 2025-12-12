# Arduino for lock

This arduino physically moves an external lock, to either lock or unlock a door from the inside.

## Config file

To run the Arduino, create a file called `Config.h`.<br>
Fill in the following code:

```
// WIFI
#define WIFI_SSID ""
#define WIFI_PASSWORD ""
#define WIFI_STATIC_IP "x.x.x.x"
#define WIFI_SUBNET_MASK "x.x.x.x"
#define WIFI_GATEWAY "x.x.x.x"
#define WIFI_DNS_SERVER "x.x.x.x"

// MQTT
#define MQTT_HOSTNAME "x.x.x.x"
#define MQTT_PORT 1883
#define MQTT_USERNAME ""
#define MQTT_PASSWORD ""

// Motor
#define MOTOR_PIN 3

// Button
#define PAIR_BUTTON_PIN 2

// Light
#define LIGHT_PIN 11
```
