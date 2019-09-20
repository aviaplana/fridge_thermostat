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

bool Encoder::hasNewInteraction() {
    bool hasInteraction = interruption_flag;
    interruption_flag = false;
    return hasInteraction;
}

void Encoder::manageInterrupt() {
    if (!interruption_flag) {
        interruption_millis = millis();
        
        if (!is_first_interruption() && ((millis() - interruption_millis) > 200)) {
            interruption_flag = true;
            if (digitalRead(CLK_PIN)) {
            
                if(!digitalRead(DT_PIN)) {
                    interaction_direction = RIGHT;
                } else {
                    interaction_direction = LEFT;
                }
            }
        }
    }
}

bool Encoder::is_first_interruption() {
    return (millis() - interruption_millis) >= MILLIS_NEW_INTERRUPTION;
}
