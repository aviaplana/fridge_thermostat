#ifndef FRIDGE_MQTT_H
#define FRIDGE_MQTT_H
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

class Mqtt {
    public:
        Mqtt();
        void setServer(char*, uint16_t);
        bool connect(char*, char*, char*);
        bool isConnected();
        void sendMessage(char*, char*);

    private:
        WiFiClient espClient;
        PubSubClient client;
};

#endif