#ifndef CONFIG_ESP_H
#define CONFIG_ESP_H
#include "Arduino.h"

class DebugMode {
    public:
        DebugMode(const char* TAG) {
            this->TAG = String(TAG);
        }
        void SET_DEBUG(bool state) {
            isDebuging = state;
        }
        void DEBUG(const char* MSG) {
            if (isDebuging)
                Serial.printf("[%s] => %s\n", this->TAG.c_str(), MSG);
        }
    private:
        bool isDebuging = true;
        String TAG;
};

#endif