#include <PubSubClient.h>
#include <ArduinoJson.h>

class MqttManager {
  char state_topic[64]; // State of the Arduino
  char command_topic[64]; // State change from Home Assistant
  char discovery_topic[64]; // Used for Home Assistant discovery

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
    }

  public:
    void SetupTopics(const char* mac_address) {
      snprintf(this->state_topic, sizeof(this->state_topic),
               "homeassistant/lock/%s/state", mac_address);
      snprintf(this->command_topic, sizeof(this->command_topic),
               "homeassistant/lock/%s/set", mac_address);
      snprintf(this->discovery_topic, sizeof(this->discovery_topic),
               "homeassistant/lock/%s/config", mac_address);
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

      bool success = client.publish(topic, message, true);
    }
  
  public:
    void SetCallback(void (*callback)(char* topic, byte* payload, unsigned int length)) {
      client.setCallback(callback);
    }
};