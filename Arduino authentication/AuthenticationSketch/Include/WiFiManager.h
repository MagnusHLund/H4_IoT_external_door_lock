#ifndef MAGNUSSY_IOT_PROJECT_ARDUINO_AUTHENTICATION_WIFIMANAGER_H
#define MAGNUSSY_IOT_PROJECT_ARDUINO_AUTHENTICATION_WIFIMANAGER_H

#endif //MAGNUSSY_IOT_PROJECT_ARDUINO_AUTHENTICATION_WIFIMANAGER_H

// WiFiManager.h
#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include <WiFi.h>
#include <Arduino.h>

class WiFiManager {
public:
    // Declare NetworkConfig for static IP configuration
    struct NetworkConfig {
        IPAddress local_ip;
        IPAddress gateway;
        IPAddress subnet;
    };

    // Initialize with credentials
    WiFiManager(const char* ssid, const char* password, const NetworkConfig* networkConfig = nullptr);

    // Connect to network and block until connected
    void connect();

    // Returns current IP address
    IPAddress getLocalIP();

    // Check if WiFi is connected
    bool isConnected();

    // Get WiFiClient
    WiFiClient& getClient() { return _client; }

private:
    const char* _ssid;
    const char* _password;
    const NetworkConfig* _networkConfig;
    WiFiClient _client;
};

#endif
