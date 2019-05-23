#ifndef DISPLAY_H
#define DISPLAY_H
#include "fridge_data.h"
#include <Adafruit_SSD1306.h>

class Display {
        Adafruit_SSD1306 display;
        
    public:
        Display(uint16_t, uint16_t);
        void begin(uint16_t);
        void printFridgeData(FridgeData);
        void printGoalFullScreen(const char*) {

    private:
        void drawSeparations();
        void printTemperature(const char*);
        void printHumidity(const char*);
        void printGoal(const char*);
        void drawConnection();
        void drawWarning();
        void drawEngine();
        void drawDoor();
};

#endif
