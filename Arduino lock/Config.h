struct Config {
  uint32_t magic;

  char wifi_ssid[32];
  char wifi_password[64];
  char wifi_static_ip[16];
  char wifi_subnet_mask[16];
  char wifi_gateway[16];
  char wifi_dns_server[16];

  char mqtt_hostname[32];
  int  mqtt_port;
  char mqtt_username[32];
  char mqtt_password[64];

  int motor_pin;
  int pair_button_pin;
};
