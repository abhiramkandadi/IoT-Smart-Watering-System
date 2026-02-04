#include <DHT.h>
#include <ESP32Servo.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include "SystemLogic.h"

// Pin definitions
const int DHT_PIN = 25;   
const int PHOTOCELL_PIN = 34;
const int SOIL_PIN = 35;
const int PUMP_PIN = 4;

// WiFi Configuration - Replace with your own credentials
const char* WIFI_NAME = "YOUR_WIFI_SSID";
const char* WIFI_PASS = "YOUR_WIFI_PASSWORD";

// MQTT Configuration
const char* MQTT_SERVER = "YOUR_MQTT_BROKER_URL";
const char* MQTT_USER   = "YOUR_MQTT_USERNAME";
const char* MQTT_PASS   = "YOUR_MQTT_PASSWORD";
const int   MQTT_PORT   = 8883;

// Deployment Info
const String YEAR = "2025";
const String CLASS = "ENGR111";
const String SECTION = "X";       // Changed for anonymity
const String GROUP_NUMBER = "XX"; // Changed for anonymity

// Soil humidity conditions
const int SOIL_MAXWET = 650;
const int SOIL_MAXDRY = 0;

// Pump Config
const int PUMP_ON_ANGLE  = 180;
const int PUMP_OFF_ANGLE = 90;

const int publishInterval = 600000; // 10 minutes

void setup() {
  Serial.begin(115200); //

  wifi_start();
  mqtt_start();
  enable_sensors();
  dht.begin();
  pinMode(SOIL_PIN, INPUT);
  pinMode(PHOTOCELL_PIN, INPUT);
}

void loop() {
  mqtt_loop();

  float Temperature = dht.readTemperature();
  float Humidity    = dht.readHumidity();
  int rawSoil = analogRead(SOIL_PIN);
  int soilPercent = map(rawSoil, SOIL_MAXWET, SOIL_MAXDRY, 100, 0);
  int lightValue = analogRead(PHOTOCELL_PIN);
  double voltage = (lightValue / 4095.0) * 3.3;

  if (soilPercent < 50) {
    Serial.println("Soil dry — pump ON");
    mypump.attach(PUMP_PIN, 1000, 2000);
    mypump.write(PUMP_ON_ANGLE);
    delay(9000);
    mypump.write(PUMP_OFF_ANGLE);
    delay(9000);
    mypump.detach();
  } else {
    Serial.println("Soil moist — pump OFF");
  }

  // Serial Debugging
  Serial.print("Temp: "); Serial.println(Temperature);
  Serial.print("Soil (%): "); Serial.println(soilPercent);

  char tempString[8], humString[8], soilString[8], lightString[8];
  dtostrf(Temperature, 1, 2, tempString);
  dtostrf(Humidity, 1, 2, humString);
  dtostrf(soilPercent, 1, 0, soilString);
  dtostrf(lightValue, 1, 0, lightString);

  // MQTT Publishing using placeholders
  String topicBase = YEAR + "/" + CLASS + "/" + SECTION + "/" + GROUP_NUMBER + "/";
  client.publish((topicBase + "temp").c_str(), tempString);
  client.publish((topicBase + "humidity").c_str(), humString);
  client.publish((topicBase + "light").c_str(), lightString);
  client.publish((topicBase + "soil").c_str(), soilString);

  delay(publishInterval);
}