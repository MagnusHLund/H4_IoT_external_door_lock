class Button {
  int pin;
  
  unsigned long pressStart = 0;
  bool heldTriggered = false;

  public:
    Button(int pin) : pin(pin) {}

  public:
    void Init() {
      pinMode(pin, INPUT_PULLUP);
    }

  // Check if button is currently pressed
  public:
    bool IsPressed() {
      return digitalRead(pin) == LOW;
    }

  // Check if button has been held for given ms
  public:
    bool IsHeld(unsigned long durationMs) {
      if (IsPressed()) {
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