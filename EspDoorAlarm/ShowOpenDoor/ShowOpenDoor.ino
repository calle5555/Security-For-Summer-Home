#include <ArduinoMqttClient.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include <WiFi.h>
#include "secrets.h"

char ssid[] = SSID;
char pass [] = password;

const char broker[] = "192.168.0.7";
int        port     = 1883;
const char topicMagDate[] = "Cabin/Magnet/DoorOpen";
const char topicNoAlarm[] = "Home/ESP32/NoAlarm";  

TFT_eSPI tft = TFT_eSPI();

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const long intervalBlink = 1000;
const long intervalButton = 10000;
unsigned long prevBlink = 0;
unsigned long buttonPress = 0;

bool doorAlarm = false;
bool showOption = true;
bool addNoAlarm = false;
bool screenRed = false;

byte xPos = 6;
byte yPos = 3;

void setup() {
  Serial.begin(115200);

  // Buttons on the ESP32
  pinMode(0,INPUT_PULLUP);
  pinMode(35,INPUT_PULLUP);

  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  
  connectWifi();

  Serial.println("You're connected to the network");
  Serial.println();

  mqttClient.setId("EspBoard");

  while(!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
  }

  // set the message receive callback
  mqttClient.onMessage(onMqttMessage);

  mqttClient.subscribe(topicMagDate);
}

void loop() {
  if(WiFi.status() != WL_CONNECTED)
    connectWifi();

  mqttClient.poll();

  unsigned long currentMillis = millis();

  if(!doorAlarm && currentMillis - buttonPress >= intervalButton){
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_BLACK);
  }

  if(digitalRead(0) == 0 && digitalRead(35) == 0 && showOption){
    buttonPress = currentMillis;
    showOption = false;
    Serial.println("I am pressing both");
  
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_RED);
    tft.drawString("Press left button", 40, 10, 4);
    tft.drawString("for no more", 40, 40, 4);
    tft.drawString("alarms toady", 40, 70, 4);

    doorAlarm = false;
    screenRed = false;
    addNoAlarm = true;
  }

  if(digitalRead(0) == 0 && digitalRead(35) == 1 && addNoAlarm && currentMillis - buttonPress >= 1500){
    addNoAlarm = false;
    buttonPress = currentMillis;
    
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_RED);
    tft.drawString("No more", 60, 20, 4);
    tft.drawString("alarms today", 40, 50, 4);

    mqttClient.beginMessage(topicNoAlarm);
    mqttClient.print(1);
    mqttClient.endMessage();
  }
  
  if(doorAlarm && currentMillis - prevBlink >= intervalBlink){
    prevBlink = currentMillis;
    
    if(!screenRed){
      tft.fillScreen(TFT_RED);
      screenRed = true;
    } else{
      tft.fillScreen(TFT_YELLOW);
      screenRed = false;
    }
    tft.setTextColor(TFT_BLACK);
    tft.drawString("Warning!", 60, 10, 4);
    tft.drawString("Door opened", 40, 40, 4);
    tft.drawString("Reset?", 70,70,4);
    tft.drawString("Press buttons", 40,100,4);
  }
}

void connectWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void onMqttMessage(int messageSize){
  addNoAlarm = false;
  doorAlarm = true;
  showOption = true;
}
