class Light {
  int light_pin;

  public:
    Light(int light_pin) : light_pin(light_pin) {
    } 

  public:
    void init() {
      pinMode(light_pin, OUTPUT);
    }

  public:
    void turnOn() {
      digitalWrite(light_pin, HIGH);
    }

  public:
    void turnOff() {
      digitalWrite(light_pin, LOW);
    }

  public:
    void blink(unsigned long interval, int blink_amount) {
      for (int i = 0; i < blink_amount; i++) {
        turnOn();
        delay(interval);
        turnOff();
        delay(interval);
      }
    }
};