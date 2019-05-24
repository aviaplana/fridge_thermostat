#ifndef DISPLAY_H
#define DISPLAY_H
#include "fridge_data.h"
#include <Adafruit_SSD1306.h>

#define DISPLAY_ADDRESS 0x3C

enum Screen {
    SET_GOAL_SCREEN, MAIN_SCREEN
};

class Display {
    Screen current_screen;
    Adafruit_SSD1306* display = new Adafruit_SSD1306(128, 64);
        
    public:
        void begin();
        void printMainScreen(FridgeData);
        void printGoalFullScreen(const char*);
        Screen getCurrentScreen() { return current_screen; }

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
