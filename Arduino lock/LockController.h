#include "Motor.h"
#include "LockCommand.h"

class LockController {
  static LockController* instance;

  Motor motor;
  MqttManager& mqttManager;

  public:
    LockController(Motor motor, MqttManager& mqttManager)
      : motor(motor), mqttManager(mqttManager) {
        instance = this;
      }

  public:
    void Init() {
      motor.Init();

      mqttManager.SetCallback(StaticCallback);
    }

  public:
    static void StaticCallback(char* topic, byte* payload, unsigned int length) {
      if (instance) {
        instance->UpdateLockState(topic, payload, length);
      }
    }

  private:
    void UpdateLockState(char* topic, byte* payload, unsigned int length) {
      char message[64];

      memcpy(message, payload, length);
      message[length] = '\0'; // terminate string

      if (strcmp(message, "LOCK") == 0) {
        LockDoor();
      } else if (strcmp(message, "UNLOCK") == 0) {
        UnlockDoor();
      } else {
        Serial.println("Unknown command");
      }
    }

  private: 
    void LockDoor() {
      motor.TurnDegrees(0);

      mqttManager.PublishMessage("LOCKED");
    }

  private:
    void UnlockDoor() {
      motor.TurnDegrees(90);

      mqttManager.PublishMessage("UNLOCKED");
    }

  private:
    char* CreateStateUpdateJson(char* state) {
      StaticJsonDocument<100> doc;

      doc["state"] = state;

      static char buffer[256];
      serializeJson(doc, buffer);

      return buffer;
    }

  private: 
    bool DeserializeJsonPayload(byte* payload, unsigned int length, LockCommand& outCmd) { 
      StaticJsonDocument<256> doc; 
      DeserializationError error = deserializeJson(doc, payload, length); 
      
      if (error) { 
        Serial.print("JSON deserialization failed: "); 
        Serial.println(error.c_str()); 
        return false; 
      } 
      
      outCmd = LockCommand::fromJson(doc); 
      return true; 
    }
};

// To prevent error when compiling
LockController* LockController::instance = nullptr;