#ifndef ENCODER_H
#define ENCODER_H
#include <stdint.h>

class Encoder {
    public:
        enum Direction {
            LEFT, RIGHT
        };

        Encoder(uint8_t pin_clk, uint8_t pin_dt);
        bool hasNewInteraction() { return interruption_flag; }
        Direction getInteractionDirection() { return interaction_direction; };
        void manageInterrupt();
        void begin();
        uint8_t getInterruptNumber();

    private:
        uint8_t CLK_PIN;
        uint8_t DT_PIN;

        volatile bool interruption_flag = false;
        volatile Direction interaction_direction;
};

#endif