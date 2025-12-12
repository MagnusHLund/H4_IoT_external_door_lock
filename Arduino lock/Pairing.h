class Pairing {
  WiFiManager& wiFiManager;
  MqttManager& mqttManager;

  Button& button;
  Light& light;

  public:
    Pairing(WiFiManager& wiFiManager, MqttManager& mqttManager, Button& button, Light& light) 
      : wiFiManager(wiFiManager), mqttManager(mqttManager), button(button), light(light) {}

  public:
    void Init() {
      button.Init();
      light.Init();

      PairToHomeAssistant();
    }

  public:
    void HandlePairingButton() {
      int fiveSeconds = 5000;

      if (button.IsHeld(fiveSeconds)) {
        PairToHomeAssistant();
        light.Blink(125, 5);
      }
    }

  public:
    void PairToHomeAssistant() {
      char* mac_address = wiFiManager.GetMacAddress(true);
      char* message = formatDiscoveryMessageJson(mac_address);

      mqttManager.PublishMessage(message, mqttManager.GetDiscoveryTopic());
      Serial.println("Sent discovery message");
    }

  private:
    char* formatDiscoveryMessageJson(char* mac_address) {
      StaticJsonDocument<512> doc;

      const char* command_topic = mqttManager.GetCommandTopic();
      const char* state_topic = mqttManager.GetStateTopic();

      doc["name"]           = "Arduino Door Lock";
      doc["unique_id"]      = mac_address; 
      doc["command_topic"]  = command_topic;
      doc["state_topic"]    = state_topic;
      doc["payload_unlock"] = "UNLOCK";
      doc["payload_lock"]   = "LOCK";
      doc["state_unlocked"] = "UNLOCKED";
      doc["state_locked"]   = "LOCKED";

      JsonObject device = doc.createNestedObject("device");
      device["identifiers"] = mac_address;
      device["manufacturer"] = "Arduino";
      device["model"] = "Uno R4 WiFi";

      static char buffer[512];
      serializeJson(doc, buffer);

      return buffer;
    }
};