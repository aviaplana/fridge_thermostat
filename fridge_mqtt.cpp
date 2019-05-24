#include "fridge_mqtt.h"

void Mqtt::setServer(char* host, uint16_t port) {
    client->setServer(host, port);
}

bool Mqtt::connect(char* clientId, char* user, char* password) {
    return client->connect(clientId, user, password);
}

bool Mqtt::isConnected() {
    return client->connected();
}

void Mqtt::sendMessage(char* topic, char* message) {
    client->publish(topic, message);
}

int8_t Mqtt::getState() {
    return client->state();
}
