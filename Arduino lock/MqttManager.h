#include <PubSubClient.h>
#include <ArduinoJson.h>

class MqttManager {
  const char* state_topic = "homeassistant/sensor/arduino/state"; // State of the Arduino
  const char* command_topic = "homeassistant/sensor/arduino/command"; // State change from Home Assistant

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
    void PublishMessage(const char* message) {
      Serial.println(message);
      client.publish(state_topic, message);
    }
  
  public:
    void SetCallback(void (*callback)(char* topic, byte* payload, unsigned int length)) {
      client.setCallback(callback);
    }
};