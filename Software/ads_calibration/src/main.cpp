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

//Konstante za vrijednosti flex senozra i maksimalne kutove servo motora
// Palac
const u_int16_t THUMB_FLEXED_SENSOR = 696;
const u_int16_t THUMB_RELAXED_SENSOR = 53;
const u_int8_t MINIMAL_ANGLE_THUMB = 0;
const u_int8_t MAXIMUM_ANGLE_THUMB = 130;

// Kažiprst
const u_int16_t INDEX_FLEXED_SENSOR = 1023;
const u_int16_t INDEX_RELAXED_SENSOR = 680;
const u_int8_t MINIMAL_ANGLE_INDEX = 0;
const u_int8_t MAXIMUM_ANGLE_INDEX = 130;

// Srednjak
//Ovaj je naopačke postavljen
const u_int16_t MIDDLE_FLEXED_SENSOR = 1043;
const u_int16_t MIDDLE_RELAXED_SENSOR = 80;
const u_int8_t MINIMAL_ANGLE_MIDDLE = 130;
const u_int8_t MAXIMUM_ANGLE_MIDDLE = 0;

// Prstenjak
const u_int16_t RING_FLEXED_SENSOR = 706;
const u_int16_t RING_RELAXED_SENSOR = 10;
const u_int8_t MINIMAL_ANGLE_RING = 0;
const u_int8_t MAXIMUM_ANGLE_RING = 130;

// Mali prst
const u_int16_t LITTLE_FLEXED_SENSOR = 1036;
const u_int16_t LITTLE_RELAXED_SENSOR = 0;
const u_int8_t MINIMAL_ANGLE_SMALL = 0;
const u_int8_t MAXIMUM_ANGLE_SMALL = 130;

// Zglob
const u_int16_t MINIMAL_WRIST_ANGLE = 0; 
const u_int16_t MAXIMUM_WRIST_ANGLE = 140;

// Inicijalizacija multipleksora i Analogno Digitalnog pretvarača
TCA9548A multiplexor;
ADS1015 ads1;
ADS1015 ads2;


//Timer
unsigned long LAST_TIME = 0;
unsigned long TIMER_DELAY = 5000;

// Funkcija za čitanje vrijednosti senzora preko analogno digitalnog pretvarača koji je spojen na multipleksor, te ograničavanje vrijednosti u dozvoljenom rasponu
u_int8_t read_sensor_from_ads( ADS1015 ads, u_int8_t pinNumber, u_int16_t relaxedSensor, u_int16_t flexedSensor, u_int8_t minimalAngle, u_int8_t maximumAngle ){
  
  uint16_t sensorReadValue = ads.readADC( pinNumber );
    if ( sensorReadValue < 0 ){
      sensorReadValue = relaxedSensor;
  } else if ( sensorReadValue > flexedSensor )
  {
    sensorReadValue = flexedSensor;
  }

  u_int8_t mappedValue;

  mappedValue = sensorReadValue >> 2;
  u_int8_t constrainedMappedValue = constrain(mappedValue, minimalAngle, maximumAngle);

  return constrainedMappedValue;
}


// Funkcija za upravljanje multipleksorom i analogno digitalnim pretvaračem kako bi se mogli očitati senzori

void read_sensors(){

  multiplexor.openChannel(0);
  
  delay(100);


 thumbValue = read_sensor_from_ads(ads1, ADS1ThumbPin, THUMB_RELAXED_SENSOR, THUMB_FLEXED_SENSOR, MINIMAL_ANGLE_THUMB, MAXIMUM_ANGLE_THUMB);
  indexFingerValue = read_sensor_from_ads(ads1, ADS1IndexPin, INDEX_RELAXED_SENSOR, INDEX_FLEXED_SENSOR, MINIMAL_ANGLE_INDEX, MAXIMUM_ANGLE_INDEX);
  middleFingerValue = read_sensor_from_ads(ads1, ADS1MiddlePin, MIDDLE_RELAXED_SENSOR, MIDDLE_FLEXED_SENSOR, MINIMAL_ANGLE_MIDDLE, MAXIMUM_ANGLE_MIDDLE);
  ringFingerValue = read_sensor_from_ads(ads1, ADS1RingPin, RING_RELAXED_SENSOR, RING_FLEXED_SENSOR, MINIMAL_ANGLE_RING, MAXIMUM_ANGLE_RING);

  multiplexor.closeChannel(0);

  multiplexor.openChannel(1);

  delay(100);

  smallFingerValue = read_sensor_from_ads(ads2, ADS2LittlePin, LITTLE_RELAXED_SENSOR, LITTLE_FLEXED_SENSOR, MINIMAL_ANGLE_SMALL, MAXIMUM_ANGLE_SMALL);

  servoWristValue = analogRead(17);

  multiplexor.closeChannel(1);


  Serial.print("thumbFingerValue: ");
  Serial.print(thumbValue);

  Serial.print(" , indexFingerValue: ");
  Serial.print(indexFingerValue);

  Serial.print(" , middleFingerValue: ");
  Serial.print(middleFingerValue);

  Serial.print(" , ringFingerValue: ");
  Serial.print(ringFingerValue);

  Serial.print(" , smallFingerValue: ");
  Serial.print(smallFingerValue);
  
  Serial.print(" , servoWristValue: ");
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

  // Uvijet za timer, koji pri isticanju očitava i ispisuje vrijednosti senzora
 if ((millis() - LAST_TIME) > TIMER_DELAY) {
    
    read_sensors();

    //Reset timer-a
    LAST_TIME = millis();

  }
}



 