#ifndef FRIDGE_SENSORS_H
#define FRIDGE_SENSORS_H
#include <BME280I2C.h>

class Sensors {
    BME280I2C bme; 

    public:
        Sensors();
        float getTemperature();
        float getHumidity();
        float getPressure();
        bool initialize();
};

#endif