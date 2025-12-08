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
    MQTT(const char* server_hostname, int server_port)
      : client(wifiClient) {
      this->server_hostname = server_hostname;
      this->server_port = server_port;
    }

  public:
    void Connect() {
      client.setServer(server_hostname, server_port);
      client.setCallback(callback);
    }
  
  public:
    void EnsureConnectivity() {
      while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        char* clientId = "ArduinoClient-" + String(random(0xffff), HEX);

        if (client.connect(clientId.c_str(), mqtt_username, mqtt_password)) {
          Serial.println("connected");
          client.subscribe("radar/distance"); 
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
    void SetCallback(/* something here idk */) {

    }
};