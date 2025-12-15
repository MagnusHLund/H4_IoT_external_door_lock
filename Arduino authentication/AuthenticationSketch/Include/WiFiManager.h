#include <WiFiS3.h>

class WiFiManager {
  const char* wifi_ssid;
  const char* wifi_password;

  IPAddress local_IP;
  IPAddress dns_server;
  IPAddress gateway;
  IPAddress subnet;

  public:
    WiFiManager(const char* wifi_ssid, const char* wifi_password, String local_IP, String gateway, String subnet, String dns_server = "1.1.1.1")
      : wifi_ssid(wifi_ssid), wifi_password(wifi_password) {
      if (!this->local_IP.fromString(local_IP)) {
        Serial.println("Invalid static IP!");
      }
      if (!this->subnet.fromString(subnet)) {
        Serial.println("Invalid subnet!");
      }
      if (!this->gateway.fromString(gateway)) {
        Serial.println("Invalid gateway!");
      }
      if (!this->dns_server.fromString(dns_server)) {
        Serial.println("Invalid DNS!");
      }
    }

  public:
    void Connect() {
      delay(10);
      Serial.println("Connecting to WiFi...");

      WiFi.config(local_IP, dns_server, gateway, subnet);

      WiFi.begin(wifi_ssid, wifi_password);

      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }

      Serial.println("\nWiFi connected.");
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
    }

  public:
    void EnsureConnectivity() {
      if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi lost, reconnecting...");
        Connect();
      }
    }

  public:
    char* GetMacAddress(bool remove_colons = false) {
      static char macStr[18];
      byte mac[6];
      WiFi.macAddress(mac);
    
      if (remove_colons) {
        snprintf(macStr, sizeof(macStr), "%02X%02X%02X%02X%02X%02X",
                 mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
      } else {
        snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
                 mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
      }
    
      return macStr; 
    }
};