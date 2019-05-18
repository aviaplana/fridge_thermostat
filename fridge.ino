#include "config.h"
#include "fridge_data.h"
#include "fridge_mqtt.h"
#include "fridge_wifi.h"
#include "fridge_sensors.h"

#define POTENTIOMETER A0
#define RELAY_PIN 13

#define TEMPERATURE_TOLERANCE .5
#define MIN_POT 77
#define MAX_POT 952
#define MIN_TEMP 0
#define MAX_TEMP 100
#define RECONNECT_TIME 5000
#define PUBLISH_FREQUENCY 10000
#define CHECK_FRIDGE_FREQUENCY 5000

#define mqtt_topic "fridge/status"

Wifi wifi;
Mqtt mqtt;
FridgeData data;
Sensors sensors;

unsigned long last_millis_reconnect = 0;
unsigned long last_millis_publish = 0;
unsigned long last_millis_check_fridge = 0;

void setup() {
  Serial.begin(9600);

  set_pins();
  connect_wifi_and_mqtt();
  

  while(!sensors.initialize()) {
    Serial.println("Unable to initialize sensors!");
    delay(1000);
  }

  delay(100);
}

void set_pins() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
}

bool connect_wifi() {
  struct Wifi::ConnectionParams params;
   strcpy(params.ssid, "ap_chaos");
   strcpy(params.password, "LaPutaClau_7");
   return wifi.connect(params);
}

float read_goal_temperature() {
  int samples = 15;
  int temp_pod = 0;

  for (int i = 0; i < samples; i++) {    
    temp_pod += analogRead(POTENTIOMETER);
    delay(70);
  }
  
  temp_pod /= samples;
  float goal = map(temp_pod, MIN_POT, MAX_POT, MAX_TEMP, MIN_TEMP) / 10.;

  return goal;
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

  mqtt.sendMessage(mqtt_topic, message);
                                
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

  if (success) {
    Serial.println(F("Connected successfully!"));
  } else {
    Serial.println(F("Couldn't connect."));
  }

  return success;
}

void connect_wifi_and_mqtt() {
  if (reconnection_interval_passed()) {

    if (!wifi.isConnected()) {
      connect_wifi();
    } 

    if (wifi.isConnected()) {
      bool success = connect_mqtt();
      if (!success) {
        Serial.print(F("Trying again in "));
        Serial.print(RECONNECT_TIME / 1000);
        Serial.println(F(" seconds"));
      }

      last_millis_reconnect = millis();
    }
  }
}

bool reconnection_interval_passed() {
  return millis() - last_millis_reconnect > RECONNECT_TIME;
}

bool can_send_data() {
  bool publish_interval_passed = (millis() - last_millis_publish) > PUBLISH_FREQUENCY;
  return publish_interval_passed && mqtt.isConnected();
}

bool check_interval_passed() {
  return (millis() - last_millis_check_fridge) > CHECK_FRIDGE_FREQUENCY;
}

void read_sensors_and_operate_compressor() {
    float goal = read_goal_temperature();
    data.goal_temperature = goal;

    set_fridge_data();
    
    if (data.hasValidData()) {    
      set_compressor_if_required();
      print_fridge_data();
    } else {
      Serial.println(F("Failed to read from sensor"));
    }
}

void reconnect_if_required() {
    if (!mqtt.isConnected()) {
      connect_wifi_and_mqtt();
    }
}

void loop() {
  if (check_interval_passed()) {
    read_sensors_and_operate_compressor();
    last_millis_check_fridge = millis();
  }

  if (can_send_data()) {
    reconnect_if_required();
    send_data_mqtt();    
  }
  
  delay(500);
}
