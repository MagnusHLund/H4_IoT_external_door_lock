class LockManager {
  public:
    void callback(char* topic, byte* payload, unsigned int length) {
      Serial.print("Message arrived [");
      Serial.print(topic);
      Serial.print("] ");

      String message;
      for (unsigned int i = 0; i < length; i++) {
        message += (char)payload[i];
      }
      Serial.println(message);

      // Example: toggle LED based on command
      if (String(topic) == command_topic) {
        if (message == "ON") {
          digitalWrite(LED_BUILTIN, HIGH);
        } else if (message == "OFF") {
          digitalWrite(LED_BUILTIN, LOW);
        }
      }
    }
}