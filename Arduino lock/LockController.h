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
    void init() {
      motor.init();

      mqttManager.setCallback(staticCallback);
    }

  public:
    static void staticCallback(char* topic, byte* payload, unsigned int length) {
      if (instance) {
        instance->updateLockState(topic, payload, length);
      }
    }

  private:
    void updateLockState(char* topic, byte* payload, unsigned int length) {
      char message[64];

      memcpy(message, payload, length);
      message[length] = '\0'; // terminate string

      if (strcmp(message, "LOCK") == 0) {
        lockDoor();
      } else if (strcmp(message, "UNLOCK") == 0) {
        unlockDoor();
      } else {
        Serial.println("Unknown command");
      }
    }

  private: 
    void lockDoor() {
      motor.turnDegrees(0);

      mqttManager.publishMessage("LOCKED");
    }

  private:
    void unlockDoor() {
      motor.turnDegrees(90);

      mqttManager.publishMessage("UNLOCKED");
    }
};

// To prevent error when compiling
LockController* LockController::instance = nullptr;