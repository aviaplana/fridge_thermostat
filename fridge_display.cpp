#include "fridge_display.h"
#include "icons.h"
#include <SPI.h>
#include <Wire.h>

void Display::begin() {
    display->begin(SSD1306_SWITCHCAPVCC, DISPLAY_ADDRESS);
    display->clearDisplay();
    display->display();
}

void Display::printMainScreen(FridgeData data) {
    display->clearDisplay();
    drawSeparations();     
    printTemperature(data.stringTemperature());
    printHumidity(data.stringHumidity());
    printGoal(data.stringGoalTemperature());
    
    if (data.isCompressorWorking()) {
        drawEngine();
    }

    if (data.isConnected()) {
        drawConnection();
    }

    if (data.isOverTemperature()) {
        drawWarning();
    }

    if (data.isDoorOpen()) {
        drawDoor();
    }
    
    display->display();
    current_screen = MAIN_SCREEN;
}

void Display::printTemperature(const char* temperature) {
    display->setTextColor(WHITE); 
    display->setTextSize(2);
    display->setCursor(23,6);
    display->print(temperature);
    display->drawXBitmap(0, 4,  icon_thermometer, ICON_HUMIDITY_WIDTH, ICON_HUMIDITY_HEIGHT, WHITE);
}

void Display::printHumidity(const char* humidity) {
    display->setTextColor(WHITE); 
    display->setTextSize(2);
    display->setCursor(23, 40);
    display->print(humidity);
    display->drawXBitmap(0, 36,  icon_humidity, ICON_HUMIDITY_WIDTH, ICON_HUMIDITY_HEIGHT, WHITE);

}

void Display::printGoal(const char* goal) {
  display->setTextSize(1);
  display->setCursor(93,4);
  display->print(goal);
}

void Display::printGoalFullScreen(const char* goal) {
    display->clearDisplay();
    display->setTextColor(WHITE);  
    display->setTextSize(4);
    display->setCursor(10,20);
    display->print(goal);
    display->display();
    current_screen = SET_GOAL_SCREEN;
}

void Display::drawConnection() {
    display->drawXBitmap(83, 22,  icon_connection, ICON_CONNECTION_WIDTH, ICON_CONNECTION_HEIGHT, WHITE);
}

void Display::drawDoor() {
    display->drawXBitmap(83, 44,  icon_door, ICON_DOOR_WIDTH, ICON_DOOR_HEIGHT, WHITE);
}

void Display::drawWarning() {
    display->drawXBitmap(105, 44,  icon_warning, ICON_WARNING_WIDTH, ICON_WARNING_HEIGHT, WHITE);
}

void Display::drawEngine() {
    display->drawXBitmap(105, 22,  icon_engine, ICON_ENGINE_WIDTH, ICON_ENGINE_HEIGHT, WHITE);
}

void Display::drawSeparations() {
  display->drawLine(80, 21, 80, 64, WHITE);
  display->drawLine(80, 21, 128, 21, WHITE);
}
