#include "fridge_display.h"
#include "icons.h"
#include <SPI.h>
#include <Wire.h>

Display::Display(uint16_t width, uint16_t height) {
    Adafruit_SSD1306 display(width, height);
}

void Display::begin(uint16_t address) {
    display.begin(SSD1306_SWITCHCAPVCC, address);
    display.clearDisplay();
    display.display();
}

void Display::printFridgeData(FridgeData data) {
    display.clearDisplay();
    drawSeparations();
    printTemperature(data.stringTemperature());
    printHumidity(data.stringHumidity());
    printHumidity(data.stringGoalTemperature());
    display.display();
}

void Display::printTemperature(const char* temperature) {
    display.drawXBitmap(0, 4,  icon_thermometer, ICON_HUMIDITY_WIDTH, ICON_HUMIDITY_HEIGHT, WHITE);
    display.setTextColor(WHITE);  
    display.setTextSize(2);
    display.setCursor(23,6);
    display.print(temperature);
}

void Display::printHumidity(const char* humidity) {
    display.drawXBitmap(0, 36,  icon_humidity, ICON_HUMIDITY_WIDTH, ICON_HUMIDITY_HEIGHT, WHITE);
    display.setTextColor(WHITE);  
    display.setTextSize(2);
    display.setCursor(23, 40);
    display.print(humidity);
}

void Display::printGoal(const char* goal) {
  display.setTextSize(1);
  display.setCursor(93,4);
  display.print(goal);
}

void Display::printGoalFullScreen(const char* goal) {
    display.clearDisplay();
    display.setTextColor(WHITE);  
    display.setTextSize(4);
    display.setCursor(10,20);
    display.print(goal);
    display.display();
}

void Display::drawConnection() {
    display.drawXBitmap(83, 22,  icon_connection, ICON_CONNECTION_WIDTH, ICON_CONNECION_HEIGHT, WHITE);
}

void Display::drawDoor() {
    display.drawXBitmap(83, 44,  icon_door, ICON_DOOR_WIDTH, ICON_DOOR_HEIGHT, WHITE);
}

void Display::drawWarning() {
    display.drawXBitmap(105, 44,  icon_warning, ICON_WARNING_WIDTH, ICON_WARNING_HEIGHT, WHITE);
}

void Display::drawEngine() {
    display.drawXBitmap(105, 22,  icon_engine, ICON_ENGINE_WIDTH, ICON_ENGINE_HEIGHT, WHITE);
}

void Display::drawSeparations() {
  display.drawLine(80, 21, 80, 64, WHITE);
  display.drawLine(80, 21, 128, 21, WHITE);
}