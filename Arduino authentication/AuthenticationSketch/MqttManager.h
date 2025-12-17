#include <PubSubClient.h>
#include <ArduinoJson.h>

class MqttManager {
  char rfidStateTopic[64]; // State of the Arduino's RFID
  char keypadStateTopic[64]; // State of the Arduino's Keypad
  char commandTopic[64]; // State change from Home Assistant
  char rfidDiscoveryTopic[64]; // Used for Home Assistant discovery
  char keypadDiscoveryTopic[64];

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
      snprintf(this->rfidStateTopic, sizeof(this->rfidStateTopic),
               "homeassistant/binary_sensor/%s/rfid/state", macAddress);
      snprintf(this->keypadStateTopic, sizeof(this->keypadStateTopic),
              "homeassistant/binary_sensor/%s/keypad/state", macAddress);
      snprintf(this->commandTopic, sizeof(this->commandTopic),
               "homeassistant/binary_sensor/%s/set", macAddress);
      snprintf(this->rfidDiscoveryTopic, sizeof(this->rfidDiscoveryTopic),
               "homeassistant/binary_sensor/%s/rfid/config", macAddress);
      snprintf(this->keypadDiscoveryTopic, sizeof(this->keypadDiscoveryTopic),
               "homeassistant/binary_sensor/%s/keypad/config", macAddress);
    }

  public:
    const char* getRfidDiscoveryTopic() {
      return rfidDiscoveryTopic;
    }

  public:
    const char* getKeypadDiscoveryTopic() {
      return keypadDiscoveryTopic;
    }

  public:
    const char* getRfidStateTopic() {
      return rfidStateTopic;
    }

  public:
    const char* getKeypadStateTopic() {
      return keypadStateTopic;
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
      bool success = client.publish(topic, message, true);
    }
  
  public:
    void setCallback(void (*callback)(char* topic, byte* payload, unsigned int length)) {
      client.setCallback(callback);
    }
};