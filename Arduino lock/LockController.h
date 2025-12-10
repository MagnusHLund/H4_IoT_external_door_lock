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
      char cmdBuffer[32];
      memcpy(cmdBuffer, payload, length);
      cmdBuffer[length] = '\0';

      if (strcmp(cmdBuffer, "LOCK") == 0) {
        LockDoor();
      } else if (strcmp(cmdBuffer, "UNLOCK") == 0) {
        UnlockDoor();
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
};

// To prevent error when compiling
LockController* LockController::instance = nullptr;