class Pairing {
  WiFiManager& wiFiManager;
  MqttManager& mqttManager;

  public:
    Pairing(WiFiManager& wiFiManager, MqttManager& mqttManager) 
      : wiFiManager(wiFiManager), mqttManager(mqttManager) {}

  public:
    void PairToHomeAssistant() {
      char* mac_address = wiFiManager.GetMacAddress();
      char* message = formatDiscoveryMessageJson(mac_address);

      char* discovery_topic = strdup(mqttManager.GetDiscoveryTopic()); 
      mqttManager.PublishMessage(message, discovery_topic);
    }

  private:
    char* formatDiscoveryMessageJson(char* mac_address) {
      StaticJsonDocument<300> doc;

      const char* command_topic = mqttManager.GetCommandTopic();
      const char* state_topic = mqttManager.GetStateTopic();

      doc["name"]           = "Arduino Door Lock";
      doc["unique_id"]      = mac_address; 
      doc["command_topic"]  = command_topic;
      doc["state_topic"]    = state_topic;
      doc["payload_lock"]   = "LOCK";
      doc["payload_unlock"] = "UNLOCK";
      doc["state_locked"]   = "LOCKED";
      doc["state_unlocked"] = "UNLOCKED";

      static char buffer[256];
      serializeJson(doc, buffer);

      return buffer;
    }
};