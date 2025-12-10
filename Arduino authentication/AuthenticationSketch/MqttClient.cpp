//
// Created by zbcyomi on 12/8/2025.
//

#include "Include/MqttClient.h"
#include <PubSubClient.h>
#include <api/IPAddress.h>

static PubSubClient client;

MqttClient::MqttClient(const IPAddress& serverIp, uint16_t port, WiFiClient& networkClient)
    : _serverIp(serverIp), _port(port), _networkClient(networkClient), _state(0)
{
    client.setClient(_networkClient);
    client.setServer(_serverIp, _port);
}

bool MqttClient::connect(const char* clientID)
{
    return client.connect(clientID);
}

void MqttClient::disconnect()
{
    client.disconnect();
}

bool MqttClient::publish(const char* topic, const char* payload)
{
    return client.publish(topic, payload);
}

bool MqttClient::connected() const
{
    return client.connected();
}

int MqttClient::state() const
{
    return client.state();
}

void MqttClient::loop()
{
    client.loop();
}