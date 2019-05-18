#include "fridge_sensors.h"
#include <BME280I2C.h>
#include <Wire.h>

Sensors::Sensors() {
  Wire.begin();
}

bool Sensors::initialize() {
    return bme.begin();
}

float Sensors::getTemperature() {
    return bme.temp(BME280::TempUnit_Celsius);
}

float Sensors::getHumidity() {
    return bme.hum();
}

float Sensors::getPressure() {
    return bme.pres(BME280::PresUnit_Pa);
}