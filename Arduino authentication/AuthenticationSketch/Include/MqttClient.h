//
// Created by zbcyomi on 12/8/2025.
//

#ifndef MAGNUSSY_IOT_PROJECT_ARDUINO_AUTHENTICATION_MQTTCLIENT_H
#define MAGNUSSY_IOT_PROJECT_ARDUINO_AUTHENTICATION_MQTTCLIENT_H

#endif //MAGNUSSY_IOT_PROJECT_ARDUINO_AUTHENTICATION_MQTTCLIENT_H

#pragma once
#include <IPAddress.h>
#include <WiFi.h>
#include <cstdint>

class MqttClient {
public:
    MqttClient(const IPAddress& serverIp, uint16_t port, WiFiClient& networkClient);

    bool connect(const char* clientID);

    void disconnect();

    bool publish(const char* topic, const char* payload);

    bool connected() const;

    int state() const;

    void loop();

private:
    IPAddress _serverIp;
    uint16_t _port;
    Client& _networkClient;
    int _state;
};