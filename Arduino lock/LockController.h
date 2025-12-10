#include "LockCommand.h"
#include "Motor.h"

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
      LockCommand cmd;
      if (DeserializeJsonPayload(payload, length, cmd)) {
        if (strcmp(cmd.command, "LOCK") == 0) {
          LockDoor();
        } 
        else if (strcmp(cmd.command, "UNLOCK") == 0) {
          UnlockDoor();
        }
      }
    }

  private: 
    void LockDoor() {
      motor.TurnDegrees(90);

      mqttManager.PublishMessage("LOCKED");
    }

  private:
    void UnlockDoor() {
      motor.TurnDegrees(0);

      mqttManager.PublishMessage("UNLOCKED");
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

  private:
    char* CreateStateUpdateJson(char* state) {
      StaticJsonDocument<100> doc;

      doc["state"] = state;

      static char buffer[256];
      serializeJson(doc, buffer);

      return buffer;
    }
};

// To prevent error when compiling
LockController* LockController::instance = nullptr;