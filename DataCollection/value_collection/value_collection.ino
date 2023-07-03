#include <WiFi.h>
#include <NTPClient.h>
#include <ArduinoJson.h>
#include <ArduinoMqttClient.h>
#include "secrets.h"

char ssid[] = SSID;
char pass [] = password;

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

//mqttClient.setUsernamePassword(MQTTUser, MQTTPass);

const char broker[] = "192.168.0.7";
int        port     = 1883;
const char topicDht[]  = "Cabin/Dht11";
const char topicMag[]  = "Cabin/Magnet/DoorOpen";
const char topicMagDate[] = "Cabin/Magnet/Date";  
  
const long magInterval = 10000;
unsigned long magPrev = 0;

const long dhtInterval = 30000;
unsigned long dhtPrev = 0;

byte dhtData[5];

int magPin = 28;
int dhtPin = 15;

int lastTemp = 26;
int lastHum = 50;

char jsonString[2048];

void setup() {
  Serial.begin(115200);
  
  pinMode(dhtPin, OUTPUT);
  
  connectWifi();

  Serial.println("You're connected to the network");
  Serial.println();

  mqttClient.setId("SensorBoard");

  while(!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();

  // set the message receive callback
  mqttClient.onMessage(onMqttMessage);

  mqttClient.subscribe(topicMagDate);
}

void loop() {

  if(WiFi.status() != WL_CONNECTED)
    connectWifi();

  mqttClient.poll();

  unsigned long currentMillis = millis();

  // Door magnet trigger check. 
  if(analogRead(magPin) < 500 && currentMillis - magPrev >= magInterval){
    magPrev = currentMillis;

    if(checkDate()){
      mqttClient.beginMessage(topicMag);
      mqttClient.print(1);
      mqttClient.endMessage();
    }
  }

  if (currentMillis - dhtPrev >= dhtInterval) {
    // save the last time a message was sent
    dhtPrev = currentMillis;
    dhtGetData();
   
    Serial.print("Current humdity = ");
    Serial.print(dhtData[0], DEC); //Displays the integer bits of humidity;
    Serial.print('.');
    Serial.print(dhtData[1], DEC); //Displays the decimal places of the humidity;
    Serial.println('%');
    Serial.print("Current temperature = ");
    Serial.print(dhtData[2], DEC); //Displays the integer bits of temperature;
    Serial.print('.');
    Serial.print(dhtData[3], DEC); //Displays the decimal places of the temperature;
    Serial.println('C');

    if(abs(int(dhtData[2]) - lastTemp) < 15 && abs(int(dhtData[0]) - lastHum) < 30){
      mqttClient.beginMessage(topicDht);
      StaticJsonDocument<256> doc;
      doc["Hum"]["int"] = int(dhtData[0]);
      doc["Hum"]["dec"] = int(dhtData[1]);
      doc["Temp"]["int"] = int(dhtData[2]);
      doc["Temp"]["dec"] = int(dhtData[3]);
      serializeJson(doc, mqttClient);
      mqttClient.endMessage(); 
    }

    lastTemp = int(dhtData[2]);
    lastHum = int(dhtData[0]);
    
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

byte dhtRead()
{
 byte data;
 for(int i = 0; i < 8; i++)
 {
 if(digitalRead(dhtPin) == LOW)
 {
 while(digitalRead(dhtPin) == LOW); // wait 50us;
 delayMicroseconds(30); // Duration of high level determine whether data is 0 or 1
 if(digitalRead(dhtPin) == HIGH)
 data |= (1<<(7 - i)); //High in the former, low in the post;
 while(digitalRead(dhtPin) == HIGH); //Data '1', waiting for next bit
 }
 }
 return data;
}

void dhtGetData()
{
 digitalWrite(dhtPin, LOW); //Pull down the bus to send the start signal;
 delay(30); //The delay is greater than 18 ms so that DHT 11 can detect the start signal;
 digitalWrite(dhtPin, HIGH);
 delayMicroseconds(40); //Wait for DHT11 to respond;
 pinMode(dhtPin, INPUT);
 while(digitalRead(dhtPin) == HIGH);
 delayMicroseconds(80); //The DHT11 responds by pulling the bus low for 80us;
 if(digitalRead(dhtPin) == LOW);
 delayMicroseconds(80); //DHT11 pulled up after the bus 80us to start sending data;
 for(int i = 0; i < 4; i++) //Receiving data, check bits are not considered;
 dhtData[i] = dhtRead();
 pinMode(dhtPin, OUTPUT);
 digitalWrite(dhtPin, HIGH); //After release of bus, wait for host to start next signal
}

void setClock() {
  NTP.begin("ntp.netnod.se");
  NTP.waitSet();
}

bool checkDate(){
  int curDay, curMonth, curYear;
  setClock();
  time_t now = time(nullptr);
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);
  curDay = timeinfo.tm_mday;
  curMonth = timeinfo.tm_mon+1;
  curYear = timeinfo.tm_year+1900;
  
  DynamicJsonDocument doc(2048);
  deserializeJson(doc, jsonString);
  
  const char* date = doc[String(curYear)][String(curMonth)];
  if(!date)
    return false;

  Serial.println(date);
  char dayArray[5];
  sprintf(dayArray, "%d", curDay);
  if(strstr(date, dayArray) != NULL)
    return false;

  return true;
}

void onMqttMessage(int messageSize){
  char tmp[2048];
  DynamicJsonDocument doc(2048);
  deserializeJson(doc, mqttClient);
  serializeJson(doc, tmp);
  strcpy(jsonString, tmp);
 }
