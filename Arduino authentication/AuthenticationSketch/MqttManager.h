#include <PubSubClient.h>
#include <ArduinoJson.h>

class MqttManager {
  char rfid_state_topic[64]; // State of the Arduino's RFID
  char keypad_state_topic[64]; // State of the Arduino's Keypad
  char command_topic[64]; // State change from Home Assistant
  char rfid_discovery_topic[64]; // Used for Home Assistant discovery
  char keypad_discovery_topic[64];

  WiFiClient wifiClient;
  PubSubClient client;

  const char* server_hostname;
  int server_port;
  const char* mqtt_username;
  const char* mqtt_password;

  public:
    MqttManager(const char* server_hostname, int server_port, const char* mqtt_username, const char* mqtt_password)
      : client(wifiClient), server_hostname(server_hostname), server_port(server_port), mqtt_username(mqtt_username), mqtt_password(mqtt_password) {}

  public:
    void Connect() {
      client.setBufferSize(512);
      client.setServer(server_hostname, server_port);

      EnsureConnectivity();
    }

  public:
    void SetupTopics(const char* mac_address) {
      snprintf(this->rfid_state_topic, sizeof(this->rfid_state_topic),
               "homeassistant/lock_authentication/%s/rfid/state", mac_address);
      snprintf(this->keypad_state_topic, sizeof(this->keypad_state_topic),
              "homeassistant/lock_authentication/%s/keypad/state", mac_address);
      snprintf(this->command_topic, sizeof(this->command_topic),
               "homeassistant/lock_authentication/%s/set", mac_address);
      snprintf(this->rfid_discovery_topic, sizeof(this->rfid_discovery_topic),
               "homeassistant/lock_authentication/%s/rfid/config", mac_address);
      snprintf(this->keypad_discovery_topic, sizeof(this->keypad_discovery_topic),
               "homeassistant/lock_authentication/%s/keypad/config", mac_address);
    }

  public:
    const char* GetRfidDiscoveryTopic() {
      return rfid_discovery_topic;
    }

  public:
    const char* GetKeypadDiscoveryTopic() {
      return keypad_discovery_topic;
    }

  public:
    const char* GetRfidStateTopic() {
      return rfid_state_topic;
    }

  public:
    const char* GetKeypadStateTopic() {
      return keypad_state_topic;
    }

  public:
    const char* GetCommandTopic() {
      return command_topic;
    }

  public:
    void EnsureConnectivity() {
      while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");

        String clientId = "ArduinoClient-";
        clientId += String(random(0xffff), HEX);

        if (client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
          Serial.println("connected");
          client.subscribe(GetCommandTopic()); 
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
    void PublishMessage(const char* message, const char* topic = nullptr) {
      if(topic == nullptr) {
        topic = rfid_state_topic;
      }

      bool success = client.publish(topic, message, true);
    }
  
  public:
    void SetCallback(void (*callback)(char* topic, byte* payload, unsigned int length)) {
      client.setCallback(callback);
    }
};