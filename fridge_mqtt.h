#ifndef FRIDGE_MQTT_H
#define FRIDGE_MQTT_H
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

class Mqtt {
    WiFiClient espClient;
    PubSubClient* client = new PubSubClient(espClient);
    
    public:
        void setServer(char*, uint16_t);
        bool connect(char*, char*, char*);
        bool isConnected();
        void sendMessage(char*, char*);
        int8_t getState();
};

#endif
