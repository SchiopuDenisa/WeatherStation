#include <WiFi.h>
#include <WiFiAP.h>

const char *SSID = "DMP_Project";
const char *PASS = "12345678";
const int port = 80;

WiFiServer server(port);

void setup() {
  Serial.begin(115200);
  Serial.println("Starting server...");
  WiFi.softAP(SSID, PASS);

  //IPAddress myIP = WiFi.softAPIP();
  server.begin();
  Serial.println("Server started");
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("--------------------------------");
    Serial.println("New Message Received:");
    
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c); 
      }
    }
  }
}