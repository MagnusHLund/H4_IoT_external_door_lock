class Light {
  int light_pin;

  public:
    Light(int light_pin) : light_pin(light_pin) {
    } 

  public:
    void Init() {
      pinMode(light_pin, OUTPUT);
    }

  public:
    void TurnOn() {
      digitalWrite(light_pin, HIGH);
    }

  public:
    void TurnOff() {
      digitalWrite(light_pin, LOW);
    }

  public:
    void Blink(unsigned long interval, int blink_amount) {
      for (int i = 0; i < blink_amount; i++) {
        TurnOn();
        delay(interval);
        TurnOff();
        delay(interval);
      }
    }
};