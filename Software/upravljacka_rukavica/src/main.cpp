//Inicijalizacija biblioteka
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <ADS1015-SOLDERED.h>
#include <TCA9548A-SOLDERED.h>

//#Definiranje SSID-a i lozinke za povezivanje na HOTSPOT (Pristupnu Točka)
#ifndef APSSID
#define APSSID "ServerRuka"
#define APPSK  "passwordzaruku"
#endif

const char* SSID = APSSID;
const char* PASSWORD = APPSK;

const char* SERVER_NAME = "http://192.168.4.1:80/setServo";

//Konstante za Pinove Flex Senzora
const u_int8_t ADS1ThumbPin = 0;
const u_int8_t ADS1IndexPin = 1;
const u_int8_t ADS1MiddlePin = 2;
const u_int8_t ADS1RingPin = 3;
const u_int8_t ADS2LittlePin = 0;
const u_int8_t ADS2WristPin = 1;

//Konstante za vrijednosti flex senozra i maksimalne kutove servo motora
// Palac
//
// Oduzeti cu 10% od svakoga radi boljih ocitavanja 

//const u_int16_t THUMB_FLEXED_SENSOR = 590;
const u_int16_t THUMB_FLEXED_SENSOR = 630;
const u_int16_t THUMB_RELAXED_SENSOR = 40;
const u_int8_t MINIMAL_ANGLE_THUMB = 0;
const u_int8_t MAXIMUM_ANGLE_THUMB = 130;

// Kažiprst
//const u_int16_t INDEX_FLEXED_SENSOR = 508;
const u_int16_t INDEX_FLEXED_SENSOR = 540;
const u_int16_t INDEX_RELAXED_SENSOR = 40;
const u_int8_t MINIMAL_ANGLE_INDEX = 0;
const u_int8_t MAXIMUM_ANGLE_INDEX = 155;

// Srednjak
//Ovaj je naopačke postavljen
const u_int16_t MIDDLE_FLEXED_SENSOR = 1043;
const u_int16_t MIDDLE_RELAXED_SENSOR = 80;
const u_int8_t MINIMAL_ANGLE_MIDDLE = 155;
const u_int8_t MAXIMUM_ANGLE_MIDDLE = 0;

// Prstenjak
//const u_int16_t RING_FLEXED_SENSOR = 652;
const u_int16_t RING_FLEXED_SENSOR = 690;
const u_int16_t RING_RELAXED_SENSOR = 40;
const u_int8_t MINIMAL_ANGLE_RING = 0;
const u_int8_t MAXIMUM_ANGLE_RING = 150;

// Mali prst
//const u_int16_t LITTLE_FLEXED_SENSOR = 942;
const u_int16_t LITTLE_FLEXED_SENSOR = 942;
const u_int16_t LITTLE_RELAXED_SENSOR = 80;
const u_int8_t MINIMAL_ANGLE_SMALL = 0;
const u_int8_t MAXIMUM_ANGLE_SMALL = 120;

// Zglob
const u_int16_t MINIMAL_WRIST_ANGLE = 0; 
const u_int16_t MAXIMUM_WRIST_ANGLE = 180;

//Vrijednosti očitane s flex senzora
u_int8_t thumbValue;
u_int8_t indexFingerValue;
u_int8_t middleFingerValue;
u_int8_t ringFingerValue;
u_int8_t smallFingerValue;
u_int8_t servoWristValue;

//Timer
unsigned long LAST_TIME = 0;
// u milisekundama
unsigned long TIMER_DELAY = 150;

// JSON U koji će se spremiti očitane vrijednosti prije slanja na ruku
const size_t JSON_BUFFER_SIZE = 256;
StaticJsonDocument<JSON_BUFFER_SIZE> doc;

char json_read_sensors[JSON_BUFFER_SIZE];

// Inicijalizacija multipleksora i Analogno Digitalnog pretvarača
TCA9548A multiplexor;
ADS1015 ads1;
ADS1015 ads2;

u_int8_t map_v2(u_int16_t x, u_int16_t in_min, u_int16_t in_max, u_int8_t out_min, u_int8_t out_max)
{
  if ((in_max - in_min) > (out_max - out_min)) {
    return (x - in_min) * (out_max - out_min+1) / (in_max - in_min+1) + out_min;
  }
  else
  {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  }
}
u_int8_t read_sensor_from_ads( ADS1015 ads, u_int8_t pinNumber, u_int16_t relaxedSensor, u_int16_t flexedSensor, u_int8_t minimalAngle, u_int8_t maximumAngle ){
  
  uint16_t sensorReadValue = ads.readADC( pinNumber );
    if ( sensorReadValue < relaxedSensor ){
      sensorReadValue = relaxedSensor;
  } else if ( sensorReadValue > flexedSensor )
  {
    sensorReadValue = flexedSensor;
  }

  
  u_int8_t mappedValue = map_v2 (sensorReadValue, relaxedSensor, flexedSensor, minimalAngle, maximumAngle);
  
  u_int8_t constrainedMappedValue = constrain(mappedValue, minimalAngle, maximumAngle);

  return constrainedMappedValue;
}

// Funkcija za čitanje vrijednosti senzora preko analogno digitalnog pretvarača koji je spojen na multipleksor, te ograničavanje vrijednosti u dozvoljenom rasponu
u_int8_t read_sensor_from_ads_middle_finger( ADS1015 ads, u_int8_t pinNumber, u_int16_t relaxedSensor, u_int16_t flexedSensor, u_int8_t minimalAngle, u_int8_t maximumAngle ){
  
  uint16_t sensorReadValue = ads.readADC( pinNumber );
    if ( sensorReadValue < relaxedSensor ){
      sensorReadValue = relaxedSensor;
  } else if ( sensorReadValue > flexedSensor )
  {
    sensorReadValue = flexedSensor;
  }

  
  u_int8_t mappedValue = map_v2 (sensorReadValue, relaxedSensor, flexedSensor, minimalAngle, maximumAngle);
  
  u_int8_t constrainedMappedValue = constrain(mappedValue, maximumAngle, minimalAngle);

  return constrainedMappedValue;
}

// Funkcija za spremanje  i pretvaranje očitanih vrijednost u JSON format
void read_sensors_to_json(JsonDocument& jsonDoc){

  multiplexor.openChannel(0);

  delay(70);
  
  thumbValue = read_sensor_from_ads(ads1, ADS1ThumbPin, THUMB_RELAXED_SENSOR, THUMB_FLEXED_SENSOR, MINIMAL_ANGLE_THUMB, MAXIMUM_ANGLE_THUMB);
  thumbValue = map_v2(thumbValue, MINIMAL_ANGLE_THUMB, MAXIMUM_ANGLE_THUMB, MAXIMUM_ANGLE_THUMB, MINIMAL_ANGLE_THUMB); 
  indexFingerValue = read_sensor_from_ads(ads1, ADS1IndexPin, INDEX_RELAXED_SENSOR, INDEX_FLEXED_SENSOR, MINIMAL_ANGLE_INDEX, MAXIMUM_ANGLE_INDEX);
  indexFingerValue = map_v2(indexFingerValue, MINIMAL_ANGLE_INDEX, MAXIMUM_ANGLE_INDEX, MAXIMUM_ANGLE_INDEX, MINIMAL_ANGLE_INDEX); 

  middleFingerValue = read_sensor_from_ads_middle_finger(ads1, ADS1MiddlePin, MIDDLE_RELAXED_SENSOR, MIDDLE_FLEXED_SENSOR, MINIMAL_ANGLE_MIDDLE, MAXIMUM_ANGLE_MIDDLE);
  ringFingerValue = read_sensor_from_ads(ads1, ADS1RingPin, RING_RELAXED_SENSOR, RING_FLEXED_SENSOR, MINIMAL_ANGLE_RING, MAXIMUM_ANGLE_RING);
  ringFingerValue = map_v2(ringFingerValue, MINIMAL_ANGLE_RING, MAXIMUM_ANGLE_RING, MAXIMUM_ANGLE_RING, MINIMAL_ANGLE_RING); 

  multiplexor.closeChannel(0);
  multiplexor.openChannel(1);

  delay(70);
  smallFingerValue = read_sensor_from_ads(ads2, ADS2LittlePin, LITTLE_RELAXED_SENSOR, LITTLE_FLEXED_SENSOR, MINIMAL_ANGLE_SMALL, MAXIMUM_ANGLE_SMALL);
  smallFingerValue =  map_v2(smallFingerValue, MINIMAL_ANGLE_SMALL, MAXIMUM_ANGLE_SMALL, MAXIMUM_ANGLE_SMALL, MINIMAL_ANGLE_SMALL); 


  u_int16_t servoReadValue;
  servoReadValue = analogRead(17);


  Serial.print("Unmapped Wrist: ");
  Serial.println(servoReadValue);

  servoReadValue = servoReadValue >> 2;
  Serial.print("Mapped Wrist: ");

  Serial.println(servoReadValue);

  //5V
  //servoWristValue = map_v2(servoReadValue, 186, 251,0, 180);
  
  //3.3V
  servoWristValue = map_v2(servoReadValue, 130, 175,0, 180);
  servoWristValue = constrain(servoWristValue, 0, 180);


  multiplexor.closeChannel(1);

  jsonDoc["thumbValue"] = thumbValue;
  jsonDoc["indexFingerValue"] = indexFingerValue;
  jsonDoc["middleFingerValue"] = middleFingerValue;
  jsonDoc["ringFingerValue"] = ringFingerValue;
  jsonDoc["smallFingerValue"] = smallFingerValue;
  jsonDoc["servoWristValue"] = servoWristValue;




  serializeJson(jsonDoc, json_read_sensors);
  Serial.println(json_read_sensors);
}


void setup() {

  doc["thumbValue"] = 0;
  doc["indexFingerValue"] = 0;
  doc["middleFingerValue"] = 0;
  doc["ringFingerValue"] = 0;
  doc["smallFingerValue"] = 0;
  doc["servoWristValue"] = 90;

// Početak Serijske komunikacije
  Serial.begin(115200);
  Serial.println();

// Inicijalizacija WiFi-a i povezivanje na zadanu pristupnu točku
  WiFi.begin(SSID, PASSWORD);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  // Pokretanje multipleksora
  multiplexor.begin();

  // Pokretanje Analogno digitalnog pretvarača
  ads1.begin();
  ads2.begin();

  ads1.setGain(0);
  ads2.setGain(0);

  ads1.setMode(0);
  ads2.setMode(0);

  multiplexor.closeAll();

}

void loop() {

  // Uvijet za timer
  if ((millis() - LAST_TIME) > TIMER_DELAY) {
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
      
      // Povezivanje na zadanu adresu
      http.begin(client, SERVER_NAME);

      // Pozivanje funkcije za očitavanje senzora
      read_sensors_to_json(doc);

      // Postavljanje header-a zahtjeva
      http.addHeader("Content-Type", "text/plain");
      // Data to send with HTTP POST
      char httpRequestData[JSON_BUFFER_SIZE];     
      // Kopiranje JSON-a očitanih senzora u niz char-a kako bi se mogli poslati na server
      strcpy(httpRequestData, json_read_sensors);
      Serial.println(httpRequestData);

      // Slanje HTTP POST-a zahtjeva
      int httpResponseCode = http.POST(String(httpRequestData));
     
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
        
      // Oslobađanje resursa
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    // Resetiranje timer-a
    LAST_TIME = millis();
  }
}

