#include "wifi_controls.h"
#include "wifi_controls_html.h"
#include <WiFi.h>

#include "config.h"

WiFiServer server(80);

void controls_setup(void (*loading_func)()) {
  Serial.println();
  if (WIFI_CREATE_ACCESS_POINT) {
    Serial.println("Creating access point...");
    Serial.printf("  SSID: %s\n", WIFI_SSID);
    Serial.printf("  Password: %s\n", WIFI_PASSWORD);
    WiFi.softAPConfig(WIFI_IP, WIFI_IP, WIFI_SUBNET);
    if(WiFi.softAP(WIFI_SSID, WIFI_PASSWORD)) {
      Serial.println("Access point created.");
    } else {
      Serial.println("Failed to create access point.");
    }
    Serial.print("IP address: ");
    Serial.println(WiFi.softAPIP());
  } else {
    Serial.printf("Connecting to \"%s\"...\n", WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    uint64_t last_dot = 0;
    while (WiFi.status() != WL_CONNECTED) {
      loading_func();

      if (millis() - last_dot > 1000) {
        Serial.print(".");
        last_dot = millis();
      }
    }
  }
  Serial.println();

  server.begin();
}

bool controls_flap_active() {
  if (server.hasClient()) {
    WiFiClient client = server.available();
    if (client) {
      String request = client.readStringUntil('\r');
      client.flush();


      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("Connection: close");
      client.println();

      if (request.indexOf("/flap") != -1) {
        client.stop();
        return true;
      }

      client.println(wifi_controls_html);

      client.stop();
      return true;
    }
  }
  return false;
}