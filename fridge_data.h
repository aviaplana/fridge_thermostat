#ifndef FRIDGE_DATA_H
#define FRIDGE_DATA_H

struct FridgeData {
        float temperature;
        float humidity;
        float pressure;
        float goal_temperature;
        bool compressor_working;
        bool is_door_open;
        bool is_over_temperature;
        bool is_connected;

        const float INVALID_DATA =  -99.;

        char* toString();
        bool hasValidData();
        const char* stringTemperature();
        const char* stringHumidity();
        const char* stringPressure();
        const char* stringGoalTemperature();
        bool isCompressorWorking() { return compressor_working; }
        bool isDoorOpen() { return is_door_open; }
        bool isOverTemperature() { return is_over_temperature; }
        bool isConnected() { return is_connected; }
        const char* stringCompressorStatus();
};

#endif