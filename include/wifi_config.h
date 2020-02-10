#ifndef WIFI_CONFIG_H
#define WIFI_CONFIG_H

#include "WiFi.h"
#include "DNSServer.h"
#include "WebServer.h"
#include "WiFiManager.h"

#define AP_SSID "M5Stick_WiFi_config"
#define AP_PASS "m5stick1234"



void setupPortal() {
    WiFiManager wifiManager;
    //reset settings - for testing
    //wifiManager.resetSettings();
    wifiManager.setSTAStaticIPConfig(IPAddress(10,0,1,99), IPAddress(10,0,1,1), IPAddress(255,255,255,0));
    WiFiManagerParameter line_token("token", "line token", "", 40);
    wifiManager.addParameter(&line_token);

    wifiManager.setTimeout(120);
    if (!wifiManager.autoConnect(AP_SSID, AP_PASS)) {
      Serial.println("failed to connect and hit timeout");
      delay(3000);
      //reset and try again, or maybe put it to deep sleep
      ESP.restart();
      delay(5000);
    }
}

#endif