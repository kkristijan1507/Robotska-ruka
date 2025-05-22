//Inicijalizacija biblioteka
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>
#include <ArduinoJson.h>
#include <Arduino.h>


//#Definiranje SSID-a i lozinke za HOTSPOT (Pristupnu Točka)
#ifndef APSSID
#define APSSID "ServerRuka"
#define APPSK  "passwordzaruku"
#endif

const char *SSID = APSSID;
const char *PASSWORD = APPSK;

//Konstante za Pinove Servo motoracv
const u_int8_t THUMB_SERVO_PIN = 0;
const u_int8_t INDEX_SERVO_PIN = 12;
const u_int8_t MIDDLE_SERVO_PIN = 13;
const u_int8_t RING_SERVO_PIN = 14;
const u_int8_t SMALL_SERVO_PIN = 15;
const u_int8_t WRIST_SERVO_PIN = 5;
 

// Postavljenje Static IP adrese kako bi se klijent mogao spojiti i nakon reseta
IPAddress apIP(192, 168, 4, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

//Otvaranje porta 80 za WebServer
ESP8266WebServer server(80);

const int JSON_BUFFER_SIZE = 96;

//Inicijalizacija Servo-a
Servo thumb;
Servo indexFinger;
Servo middleFinger;
Servo ringFinger;
Servo smallFinger;
Servo wrist;

//Vrijednosti koje će primiti od rukavice,te se ispisati na servo motore
int servoThumbValue = 0;
int servoIndexValue = 0;
int servoMiddleValue = 180;
int servoRingValue = 0;
int servoSmallValue = 0; 
int servoWristValue;

//Timer
unsigned long LAST_TIME = 0;
const long TIMER_DELAY = 90; 

//Pisanje primljenih vrijednosti na Servo Motore
void write_servos(){
    thumb.write(servoThumbValue);
    indexFinger.write(servoIndexValue);
    middleFinger.write(servoMiddleValue);
    ringFinger.write(servoRingValue);
    smallFinger.write(servoSmallValue);
    wrist.write(servoWristValue);
}


void setup() {

  //Pokretanje Serijske komunikacije
  Serial.begin(115200);

  // Postavljanje "Soft Access Point-a"
  WiFi.mode(WIFI_AP);
  WiFi.softAP(SSID, PASSWORD);
  WiFi.softAPConfig(apIP, apIP, subnet);
  //Default 192.168.4.1

  //Ispis SSID-a i Lozinke za Spajanje na WiFi server
  Serial.print("SoftAP IP Address: ");
  Serial.println(WiFi.softAPIP());

  Serial.print(F("Creating access point named: "));
  Serial.print(SSID);
  Serial.print(F(" and password: "));
  Serial.println(PASSWORD);

  //End Point na Web serveru za GET zahtjev koji vraća zadani odgovor
  server.on("/", HTTP_GET, [](){
      server.send(200, "text/html", "ESP8266 SoftAP !");
    });

  //End Point na Web serveru za POST request koji prima JSON string koji parsira vrijednosti te ih ispisuje na servo motore
  server.on("/setServo", HTTP_POST, [](){

      DynamicJsonDocument doc(2048); //Inicijalizacija Json  varijable

      DeserializationError error = deserializeJson(doc, server.arg("plain"));

      if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
      }

      servoThumbValue = doc["thumbValue"];
      servoIndexValue = doc["indexFingerValue"];
      servoMiddleValue = doc["middleFingerValue"];
      servoRingValue = doc["ringFingerValue"];
      servoSmallValue = doc["smallFingerValue"]; 
      servoWristValue = doc["servoWristValue"];

      Serial.print("servoThumbValue: ");
      Serial.println(servoThumbValue);
      Serial.print("servoIndexValue: ");
      Serial.println(servoIndexValue);
      Serial.print("servoMiddleValue: ");
      Serial.println(servoMiddleValue);
      Serial.print("servoRingValue: ");
      Serial.println(servoRingValue);
      Serial.print("servoSmallValue: ");
      Serial.println(servoSmallValue);
      Serial.print("servoWristValue: ");
      Serial.println(servoWristValue);

      server.send(200, "text/plain", "Servo angle set");
    });

  server.begin();

  //Inicijalizacija Servo-a
  thumb.attach(THUMB_SERVO_PIN);
  indexFinger.attach(INDEX_SERVO_PIN);
  middleFinger.attach(MIDDLE_SERVO_PIN);
  ringFinger.attach(RING_SERVO_PIN);
  smallFinger.attach(SMALL_SERVO_PIN);
  wrist.attach(WRIST_SERVO_PIN);
  
}

void loop() {


  //Pokretanje client handler-a
  server.handleClient();

  // Timer koji pri istjecanju ispisuje vrijednosti na servo  
  if ((millis() - LAST_TIME) > TIMER_DELAY) {
 
    write_servos();
    LAST_TIME = millis(); //reset timer-a
    
  } 
}
