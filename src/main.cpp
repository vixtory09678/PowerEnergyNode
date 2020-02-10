#include <Arduino.h>
#include "esp32ModbusRTU.h"

#include <M5StickC.h>
#include "WiFi.h"

#include "config.h"
#include "modbus_config.h"
#include "wifi_config.h"


void onDataReceive(MeterSensor meter){
  // handle hear

}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  M5.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 10);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(1);
  modbusSetup(onDataReceive);
}

void loop() {
  // put your main code here, to run repeatedly:

  // send data every 5 second
  static uint32_t lastMillis = 0;
  if (millis() - lastMillis > 5000) {
    lastMillis = millis();

    Serial.print("sending Modbus request...\n");
    // request data from meter
    sendCode(); 
  }
}







