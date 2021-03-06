#include <pgmspace.h>

#define ICON_HUMIDITY_WIDTH 21
#define ICON_HUMIDITY_HEIGHT 21
#define ICON_THERMOMETER_WIDTH 21
#define ICON_THERMOMETER_HEIGHT 21
#define ICON_CONNECTION_WIDTH 21
#define ICON_CONNECTION_HEIGHT 21
#define ICON_DOOR_WIDTH 21
#define ICON_DOOR_HEIGHT 21
#define ICON_ENGINE_WIDTH 21
#define ICON_ENGINE_HEIGHT 21
#define ICON_WARNING_WIDTH 21
#define ICON_WARNING_HEIGHT 21

static const unsigned char  icon_thermometer[] ={
   0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x80, 0x19, 0x00, 0x80, 0x10, 0x00,
   0x80, 0x10, 0x00, 0x80, 0x10, 0x00, 0x80, 0x10, 0x00, 0x80, 0x16, 0x00,
   0x80, 0x16, 0x00, 0x80, 0x16, 0x00, 0x80, 0x16, 0x00, 0x80, 0x16, 0x00,
   0xc0, 0x36, 0x00, 0x60, 0x66, 0x00, 0x20, 0x4f, 0x00, 0x20, 0x4f, 0x00,
   0x60, 0x66, 0x00, 0xc0, 0x30, 0x00, 0x80, 0x19, 0x00, 0x00, 0x0f, 0x00,
   0x00, 0x00, 0x00 };

static const unsigned char PROGMEM icon_humidity[] = {
   0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x1b, 0x00,
   0x80, 0x31, 0x00, 0xc0, 0x60, 0x00, 0x60, 0xc0, 0x00, 0x30, 0x80, 0x01,
   0x10, 0x00, 0x01, 0x18, 0x00, 0x03, 0x88, 0x31, 0x02, 0x8c, 0x19, 0x06,
   0x0c, 0x0c, 0x06, 0x0c, 0x06, 0x06, 0x0c, 0x33, 0x06, 0x88, 0x31, 0x02,
   0x18, 0x00, 0x03, 0x30, 0x80, 0x01, 0x60, 0xc0, 0x00, 0xc0, 0x71, 0x00,
   0x00, 0x1f, 0x00 };

static const unsigned char PROGMEM icon_connection[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x7f, 0x00, 0x80, 0xc1, 0x00, 0x40, 0x80, 0x00, 0x78, 0x00, 0x01,
   0xcc, 0x00, 0x01, 0x02, 0x01, 0x03, 0x03, 0x00, 0x0c, 0x01, 0x00, 0x18,
   0x01, 0x00, 0x10, 0x03, 0x00, 0x10, 0x02, 0x00, 0x08, 0x0c, 0x00, 0x0c,
   0xf0, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00 };

static const unsigned char PROGMEM icon_door[] = {
   0xf0, 0xff, 0x01, 0x10, 0xc0, 0x01, 0x10, 0xf0, 0x01, 0x10, 0xfc, 0x01,
   0x10, 0xfe, 0x01, 0x10, 0xff, 0x01, 0x10, 0xff, 0x01, 0x10, 0xff, 0x01,
   0x10, 0xff, 0x01, 0x10, 0xff, 0x01, 0x10, 0xff, 0x01, 0x10, 0xff, 0x01,
   0x10, 0xff, 0x01, 0x10, 0xff, 0x01, 0x10, 0xff, 0x01, 0xf0, 0xff, 0x01,
   0x00, 0xff, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x07, 0x00,
   0x00, 0x01, 0x00 };
   
static const unsigned char PROGMEM icon_engine[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x80, 0x1f, 0x00, 0x00, 0x06, 0x00, 0x00, 0x1f, 0x00, 0x84, 0x3f, 0x07,
   0xf4, 0xe0, 0x05, 0x34, 0x00, 0x04, 0x14, 0x00, 0x04, 0x1c, 0x00, 0x04,
   0x1c, 0x00, 0x04, 0x14, 0x80, 0x05, 0xf4, 0xc0, 0x07, 0x84, 0x61, 0x07,
   0x04, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00 };
   
static const unsigned char PROGMEM icon_warning[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x0e, 0x00,
   0x00, 0x1b, 0x00, 0x00, 0x11, 0x00, 0x80, 0x31, 0x00, 0x80, 0x20, 0x00,
   0xc0, 0x64, 0x00, 0x40, 0xc4, 0x00, 0x60, 0x84, 0x00, 0x30, 0x84, 0x01,
   0x10, 0x04, 0x01, 0x18, 0x00, 0x03, 0x08, 0x00, 0x02, 0x0c, 0x04, 0x06,
   0x06, 0x00, 0x0c, 0x03, 0x00, 0x18, 0xff, 0xff, 0x1f, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00 };
