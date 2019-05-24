#include "config.h"
#include "fridge_data.h"
#include "fridge_mqtt.h"
#include "fridge_wifi.h"
#include "fridge_sensors.h"
#include "fridge_encoder.h"
#include "fridge_display.h"

#define RELAY_PIN 13

#define TEMPERATURE_ALARM_DEGREES_OVER 10
#define TEMPERATURE_TOLERANCE .5
#define MIN_TEMP 0
#define MAX_TEMP 100
#define RECONNECT_TIME 5000
#define PUBLISH_FREQUENCY 10000
#define CHECK_FRIDGE_FREQUENCY 5000
#define GOAL_SET_DISPLAY_TIME 2000

Wifi wifi;
Mqtt mqtt;
FridgeData data;
Sensors sensors;
Display display;
Encoder encoder(D3, D4);

unsigned long last_millis_reconnect = 0;
unsigned long last_millis_publish = 0;
unsigned long last_millis_check_fridge = 0;
unsigned long last_millis_goal_set = 0;

void setup() {
  Serial.begin(9600);
  encoder.begin();
  display.begin();
  mqtt.setServer(MQTT_HOST, MQTT_PORT);

  set_pins();
  set_interrupt();
  connect_wifi_and_mqtt();
  wait_until_sensors_initialized();

  delay(100);
}

void wait_until_sensors_initialized() {
  while(!sensors.initialize()) {
    Serial.println("Unable to initialize sensors!");
    delay(1000);
  }
}

void set_pins() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
}

void set_interrupt() {
    int interruption_num = encoder.getInterruptNumber();
    attachInterrupt(interruption_num, manage_encoder_interruption, RISING);  
}

void manage_encoder_interruption() {
  encoder.manageInterrupt();
}

bool connect_wifi() {
  Serial.print(F("Connecting to Wifi..."));
  struct Wifi::ConnectionParams params;
   strcpy(params.ssid, WIFI_SSID);
   strcpy(params.password, WIFI_PASSWORD);
   return wifi.connect(params);
}

void set_fridge_data() {
  Serial.println("Reading sensor...");

  data.temperature = sensors.getTemperature();
  data.humidity = sensors.getHumidity();
  data.pressure = sensors.getPressure();
}

void set_compressor_if_required() {
  float temperature = data.temperature;
  float goal_temperature = data.goal_temperature;

  if (is_temperature_above_goal_range()) {
    turn_compressor_on_and_set_data();
  } else if (is_temperature_below_goal_range()) {
    turn_compressor_off_and_set_data();
  }
}

bool is_temperature_above_goal_range() {
  return (data.temperature - data.goal_temperature) > TEMPERATURE_TOLERANCE;
}

void turn_compressor_on_and_set_data() {
  digitalWrite(RELAY_PIN, HIGH);
  data.compressor_working = true;
}

bool is_temperature_below_goal_range() {
  return data.temperature <= (data.goal_temperature - TEMPERATURE_TOLERANCE);
}

void turn_compressor_off_and_set_data() {
  digitalWrite(RELAY_PIN, LOW);
  data.compressor_working = false;
}

void send_data_mqtt() {
  Serial.println(F("Sending data to mqtt..."));
    
  char* message = data.toString();

  mqtt.sendMessage(MQTT_TOPIC, message);
                                
  last_millis_publish = millis();
  
  Serial.print(F("Sent: "));
  Serial.println(message);

  free(message);
}

void print_fridge_data() {
  Serial.print(F("\nHumidity: "));
  Serial.println(data.humidity);
  Serial.print(F("Temperature: "));
  Serial.print(data.temperature);
  Serial.println(F(" C"));
  Serial.print(F("pressure: "));
  Serial.print(data.pressure);
  Serial.println(F(" Pa"));
  Serial.print(F("Goal temp: "));
  Serial.println(data.goal_temperature);
}

bool connect_mqtt() {
  Serial.print(F("Attempting MQTT connection as "));
  Serial.print(MQTT_USER);
  Serial.print(F("... "));

  bool success = mqtt.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASSWORD);
  data.is_connected = success;
  
  if (success) {
    Serial.println(F("Connected successfully!"));
  } else {
    Serial.print(F("Couldn't connect. RC="));
    Serial.print(mqtt.getState());
    Serial.print(F("\n"));
  }

  return success;
}

bool connect_wifi_and_mqtt() {
    if (!wifi.isConnected()) {
      if (connect_wifi()) {
        Serial.println(F("Success!"));
      } else {
        Serial.println(F("Couldn't connect."));
      }
    }

    if (wifi.isConnected()) {
      bool success = connect_mqtt();
      
      if (!success) {
        Serial.print(F("Trying again in "));
        Serial.print(RECONNECT_TIME / 1000);
        Serial.println(F(" seconds"));
      } 

      last_millis_reconnect = millis();
      return true;
    } else {
      data.is_connected = false;
    }

    return false;
}

bool reconnection_interval_passed() {
  return (millis() - last_millis_reconnect) > RECONNECT_TIME;
}

bool can_send_data() {
  bool publish_interval_passed = (millis() - last_millis_publish) > PUBLISH_FREQUENCY;
  return publish_interval_passed && mqtt.isConnected();
}

bool check_interval_passed() {
  return (millis() - last_millis_check_fridge) > CHECK_FRIDGE_FREQUENCY;
}

bool is_set_goal_display_time_over() {
  return (millis() - last_millis_goal_set) > GOAL_SET_DISPLAY_TIME;
}

void read_sensors_and_operate_compressor() {
    set_fridge_data();
    
    if (data.hasValidData()) {    
      set_compressor_if_required();
      print_fridge_data();
      data.is_over_temperature = is_over_temperature();
    } else {
      Serial.println(F("Failed to read from sensor"));
    }
}

void reconnect_if_required() {
    if (!mqtt.isConnected() && reconnection_interval_passed()) {
      connect_wifi_and_mqtt();
    }
}

void adjust_goal_temperature() {
  Encoder::Direction direction = encoder.getInteractionDirection();
  if (direction == Encoder::RIGHT) {
    data.goal_temperature += 0.1;
  } else if (direction == Encoder::LEFT){
    data.goal_temperature -= 0.1;
  }
  last_millis_goal_set = millis();
}

void update_main_screen() {
  if (is_set_goal_display_time_over()) {
    display.printMainScreen(data);
  }
}

bool is_over_temperature() {
  return data.hasValidData() && data.temperature >= (TEMPERATURE_ALARM_DEGREES_OVER + data.goal_temperature);
}

void loop() {
  if (encoder.hasNewInteraction()) {
    adjust_goal_temperature();
    const char* goal = data.stringGoalTemperature();
    display.printGoalFullScreen(goal);
  }

  if (display.getCurrentScreen() == SET_GOAL_SCREEN) {
    update_main_screen();
  }

  if (check_interval_passed()) {
    read_sensors_and_operate_compressor();
    last_millis_check_fridge = millis();
    update_main_screen();
  }

  if (can_send_data()) {
    reconnect_if_required();
    send_data_mqtt();    
  }
  
  delay(100);
}
