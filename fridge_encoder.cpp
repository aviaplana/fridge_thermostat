#include "fridge_encoder.h"
#include <Arduino.h>

Encoder::Encoder(uint8_t clk_pin, uint8_t dt_pin) {
    CLK_PIN = clk_pin;
    DT_PIN = dt_pin;
}

void Encoder::begin() {
    pinMode(CLK_PIN, INPUT);
    pinMode(DT_PIN, INPUT);
}

uint8_t Encoder::getInterruptNumber() {
    return digitalPinToInterrupt(CLK_PIN);
}

void Encoder::manageInterrupt() {
    if (!interruption_flag) {
        if (digitalRead(CLK_PIN) && !digitalRead(DT_PIN)) {
            interruption_flag = true;
            interaction_direction = RIGHT;
        } else if(digitalRead(CLK_PIN) && digitalRead(DT_PIN)) {
            interruption_flag = true;
            interaction_direction = LEFT;

        }
    }
}