#include <PubSubClient.h>
#include <ArduinoJson.h>

class MqttManager {
  const static char* state_topic; // State of the Arduino
  const static char* command_topic; // State change from Home Assistant
  const static char* discovery_topic; // Used for Home Assistant discovery

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
      client.setServer(server_hostname, server_port);
    }

  public:
    void SetupTopics(const char* mac_address) {
      static char state_topic[64];
      static char command_topic[64];
      static char discovery_topic[64];

      sprintf(state_topic, "homeassistant/lock/%s/state", mac_address);
      sprintf(command_topic, "homeassistant/lock/%s/set", mac_address);
      sprintf(discovery_topic, "homeassistant/lock/%s/config", mac_address);

      // assign to your class members
      this->state_topic     = state_topic;
      this->command_topic   = command_topic;
      this->discovery_topic = discovery_topic;
    }

  public:
    const char* GetDiscoveryTopic() {
      return discovery_topic;
    }

  public:
    const char* GetStateTopic() {
      return state_topic;
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
          client.subscribe(command_topic); 
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
        topic = state_topic;
      }

      Serial.println(message);
      client.publish(topic, message);
    }
  
  public:
    void SetCallback(void (*callback)(char* topic, byte* payload, unsigned int length)) {
      client.setCallback(callback);
    }
};

const char* MqttManager::state_topic = nullptr;
const char* MqttManager::command_topic = nullptr;
const char* MqttManager::discovery_topic = nullptr;