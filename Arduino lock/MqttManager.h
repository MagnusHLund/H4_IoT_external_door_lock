#include <PubSubClient.h>
#include <ArduinoJson.h>

class MqttManager {
  char stateTopic[64]; // State of the Arduino
  char commandTopic[64]; // State change from Home Assistant
  char discoveryTopic[64]; // Used for Home Assistant discovery

  WiFiClient wifiClient;
  PubSubClient client;

  WiFiManager& wiFiManager;

  const char* serverHostname;
  int serverPort;
  const char* mqttUsername;
  const char* mqttPassword;

  public:
    MqttManager(const char* serverHostname, int serverPort, const char* mqttUsername, const char* mqttPassword, WiFiManager& wiFiManager)
      : client(wifiClient), serverHostname(serverHostname), serverPort(serverPort), mqttUsername(mqttUsername), mqttPassword(mqttPassword), wiFiManager(wiFiManager) {}

  public:
    void connect() {
      client.setBufferSize(512);
      client.setServer(serverHostname, serverPort);

      ensureConnectivity();
    }

  public:
    void setupTopics(const char* macAddress) {
      snprintf(this->stateTopic, sizeof(this->stateTopic),
               "homeassistant/lock/%s/state", macAddress);
      snprintf(this->commandTopic, sizeof(this->commandTopic),
               "homeassistant/lock/%s/set", macAddress);
      snprintf(this->discoveryTopic, sizeof(this->discoveryTopic),
               "homeassistant/lock/%s/config", macAddress);
    }

  public:
    const char* getDiscoveryTopic() {
      return discoveryTopic;
    }

  public:
    const char* getStateTopic() {
      return stateTopic;
    }

  public:
    const char* getCommandTopic() {
      return commandTopic;
    }

  public:
    void ensureConnectivity() {
      while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");

        char* macAddress = wiFiManager.getMacAddress(true);

        if (client.connect(macAddress, mqttUsername, mqttPassword)) {
          Serial.println("connected");
          client.subscribe(getCommandTopic()); 
        } else {
          Serial.print("failed, rc=");
          Serial.print(client.state());
          Serial.println(" try again in 5 seconds");
          delay(5000);
        }
      }
      client.loop(); // Keep alive
    }

  public:
    void publishMessage(const char* message, const char* topic = nullptr) {
      if(topic == nullptr) {
        topic = stateTopic;
      }

      bool success = client.publish(topic, message, true);
    }
  
  public:
    void setCallback(void (*callback)(char* topic, byte* payload, unsigned int length)) {
      client.setCallback(callback);
    }
};