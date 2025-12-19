class Button {
  int pin;
  
  unsigned long pressStart = 0;
  bool heldTriggered = false;

  public:
    Button(int pin) : pin(pin) {}

  public:
    void init() {
      pinMode(pin, INPUT_PULLUP);
    }

  // Check if button is currently pressed
  public:
    bool isPressed() {
      return digitalRead(pin) == LOW;
    }

  // Check if button has been held for given ms
  public:
    bool isHeld(unsigned long durationMs) {
      if (isPressed()) {
        if (pressStart == 0) {
          pressStart = millis(); // first press
          heldTriggered = false;
        } else if (!heldTriggered && millis() - pressStart >= durationMs) {
          heldTriggered = true;
          return true; // just triggered
        }
      } else {
        // reset when released
        pressStart = 0;
        heldTriggered = false;
      }
      return false;
    }
};