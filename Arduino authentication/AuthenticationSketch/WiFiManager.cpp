//
// Created by zbcyomi on 12/8/2025.
//

// WiFiManager.cpp
#include "include/WiFiManager.h"

WiFiManager::WiFiManager(const char* ssid, const char* password, const NetworkConfig* networkConfig)
    : _ssid(ssid), _password(password), _networkConfig(networkConfig) {}

void WiFiManager::connect() {
    Serial.print("Connecting to WiFi: ");
    Serial.println(_ssid);

    if (_networkConfig) {
        WiFi.config(_networkConfig->local_ip, _networkConfig->gateway, _networkConfig->subnet);
    }

    WiFi.begin(_ssid, _password);

    int retries = 0;
    while (WiFi.status() != WL_CONNECTED && retries < 20) {
        delay(500);
        Serial.print(".");
        retries++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi connected!");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("\nFailed to connect to WiFi.");
    }
}

IPAddress WiFiManager::getLocalIP() {
    return WiFi.localIP();
}

bool WiFiManager::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}