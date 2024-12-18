#include "wifi_controls.h"
#include "wifi_controls_html.h"
#include <WiFi.h>

#include "config.h"

WiFiServer server(80);

void controls_setup(void (*loading_func)()) {
  if (!WIFI_CREATE_ACCESS_POINT) {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  }

  while (WiFi.status() != WL_CONNECTED) {
    loading_func();
  }
  
  Serial.print(".");
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.printf("IP address: %s\n", WiFi.localIP().toString().c_str());

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