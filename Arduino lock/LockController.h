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
};

// To prevent error when compiling
LockController* LockController::instance = nullptr;