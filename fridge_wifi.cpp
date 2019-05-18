#include "fridge_wifi.h"
#include <ESP8266WiFi.h>

bool Wifi::connect(struct ConnectionParams params) {
    WiFi.setOutputPower(0);
    WiFi.mode(WIFI_STA);
    WiFi.begin(params.ssid, params.password);
    
    waitUntilConnectedOrTimeout();

    if (isConnected()) {
        return true;
    } else {
        return false;
    }
}

void Wifi::waitUntilConnectedOrTimeout() {
    unsigned long elapsed_time = millis();

    while (!isConnected() && (millis() - elapsed_time) < TIMEOUT_CONNECT) {
        delay(500);
    }
    return ;
}

bool Wifi::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

const char* Wifi::getIp(){
    String stringIp = WiFi.localIP().toString();
    uint16_t length = stringIp.length() + 1;
    char ip[length];
    stringIp.toCharArray(ip, length);

    return ip;
}