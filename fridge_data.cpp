#include "fridge_data.h"
#include <stdlib.h>
#include <string.h>

char* FridgeData::toString() {
    char* message = (char*) calloc(90, sizeof(char));

    strcat(message, "{\"temperature\": ");
    strcat(message, stringTemperature());

    strcat(message, ", \"humidity\": ");
    strcat(message, stringHumidity());

    strcat(message, ", \"pressure\": ");
    
    strcat(message, ", \"compressor\": ");
    strcat(message, stringCompressorStatus());

    strcat(message, ", \"goal\": ");
    strcat(message, stringGoalTemperature());
    
    strcat(message, "}");

    return message;
}

bool FridgeData::hasValidData() {
    return temperature != INVALID_DATA;
}

const char* FridgeData::stringTemperature() {
    if (temperature != INVALID_DATA) {
        char char_temp[6];
        gcvt(temperature, 4, char_temp);
        return char_temp;
    } else {
        return "nan";
    }
}

const char* FridgeData::stringHumidity() {
    if (humidity != INVALID_DATA) {
        char char_humidity[6];
        gcvt(humidity, 4, char_humidity);
        return char_humidity;
    } else {
        return "nan";
    }
}

const char* FridgeData::stringPressure() {
    if (pressure != INVALID_DATA) {
        char char_pressure[6];
        gcvt(pressure, 5, char_pressure);
        return char_pressure;
    } else {
        return "nan";
    }
}

const char* FridgeData::stringCompressorStatus() {
    return compressor_working ? "1" : "0";
}

const char* FridgeData::stringGoalTemperature() {
    char char_goal[4];
    gcvt(goal_temperature, 3, char_goal);
    return char_goal;
}