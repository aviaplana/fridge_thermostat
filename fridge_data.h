#ifndef FRIDGE_DATA_H
#define FRIDGE_DATA_H

struct FridgeData {
        float temperature;
        float humidity;
        float pressure;
        bool compressor_working;
        float goal_temperature;

        const float INVALID_DATA =  -99.;

        char* toString();
        bool hasValidData();
        const char* stringTemperature();
        const char* stringHumidity();
        const char* stringPressure();
        const char* stringGoalTemperature();
        bool isCompressorWorking() { return compressor_working; }
        const char* stringCompressorStatus();
};

#endif