#include <WiFi.h>

class WiFiManager {
  IPAddress local_IP(10, 101, 161, 42);     // Desired static IP
  IPAddress dns_server(8, 8, 8, 8);         // Primary DNS
  IPAddress gateway(10, 101, 161, 1);       // Router gateway
  IPAddress subnet(255, 255, 0, 0);       // Subnet mask 

  void setup_wifi() {
  delay(10);
  Serial.println("Connecting to WiFi...");

  // Configure static IP (WiFiS3: returns void, not bool)
  WiFi.config(local_IP, dns_server, gateway, subnet);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
};