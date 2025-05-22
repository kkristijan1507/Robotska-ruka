//Inicijalizacija biblioteka
#include <Arduino.h>
#include "ADS1015-SOLDERED.h"
#include "TCA9548A-SOLDERED.h"

//Konstante za Pinove Flex Senzora
const u_int8_t ADS1ThumbPin = 0;
const u_int8_t ADS1IndexPin = 1;
const u_int8_t ADS1MiddlePin = 2;
const u_int8_t ADS1RingPin = 3;
const u_int8_t ADS2LittlePin = 0;
const u_int8_t ADS2WristPin = 1;

//Vrijednosti očitane s flex senzora

uint16_t thumbValue;
uint16_t indexFingerValue;
uint16_t middleFingerValue;
uint16_t ringFingerValue;
uint16_t smallFingerValue;
uint16_t servoWristValue;

// Inicijalizacija multipleksora i Analogno Digitalnog pretvarača
TCA9548A multiplexor;
ADS1015 ads1;
ADS1015 ads2;


//Timer
unsigned long LAST_TIME = 0;
unsigned long TIMER_DELAY = 5000;


// Funkcija za čitanje vrijednosti senzora preko analogno digitalnog pretvarača koji je spojen na multipleksor

void read_sensors(){

  //otvaranje nultog kanala multipleksora
  multiplexor.openChannel(0);
  
  delay(100);  

  //Očitavanje vrijednosti palca, kažiprsta, srednjaka i prstenjaka  koji su spojeni na prvi analogno digitalni pretvarač
  thumbValue = ads1.readADC(ADS1ThumbPin);
  indexFingerValue = ads1.readADC(ADS1IndexPin);
  middleFingerValue = ads1.readADC(ADS1MiddlePin); 
  ringFingerValue = ads1.readADC(ADS1RingPin) ;

  // Zatvaranje nultog kanala multipleksora
  multiplexor.closeChannel(0);

  // Otvaranje prvog kanala multipleksora
  multiplexor.openChannel(1);

  delay(100);

  // Očitavanje malog prsta koji je spojen na drugi analogno digitalni pretvarač
  smallFingerValue = ads2.readADC(ADS2LittlePin);

  // Očitavanje vrijednosti X osi joystick-a
  servoWristValue = analogRead(17);

  // Zatvaranje prvog kanala multipleksora
  multiplexor.closeChannel(1);

  // Ispis očitanih vrijednosti
  Serial.print("thumbFingerValue: ");
  Serial.print(thumbValue);

  Serial.print(" , indexFingerValue: ");
  Serial.print(indexFingerValue);

  Serial.print(" , middleFingerValue: ");
  Serial.print(middleFingerValue);

  Serial.print(" . ringFingerValue: ");
  Serial.print(ringFingerValue);

  Serial.print(" , smallFingerValue: ");
  Serial.print(smallFingerValue);

  Serial.print(", servoWristValue: ");
  Serial.print(servoWristValue);
  Serial.println();

}

void setup() {
  
  // Pokretanje serijske komunikacije
  Serial.begin(9600);
  Serial.println();

  // Pokretanje multipleksora
  multiplexor.begin();

  // Pokretanje Analogno digitalnog pretvarača
  ads1.setGain(0);
  ads2.setGain(0);

  ads1.setMode(0);
  ads2.setMode(0);


  multiplexor.closeAll();

}

void loop() {

    // Uvijet za timer

 if ((millis() - LAST_TIME) > TIMER_DELAY) {
    
    read_sensors();
 
    LAST_TIME = millis();

  }
}



 