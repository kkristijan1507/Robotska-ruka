//Inicijalizacija biblioteka
#include <Arduino.h>
#include <Servo.h>

// Inicijalizacija Servo-a i pin-a na koji će servo biti spojen
Servo servo;  
Servo servo2;  

const u_int8_t servoPin = 12; 

const u_int8_t servoPin2 = 0; 
void setup() {
  
  // Početak serijske komunikacije
  Serial.begin(9600);
  // spajanje Servo-a na prethodno definirani pin
  servo.attach(servoPin); 
  servo2.attach(servoPin2);
}

void loop() {

  // Čitanje unesenih vrijednosti preko serijske komunikacije
 if (Serial.available() > 0) 
  {
    int angle = Serial.parseInt(); // Parsiranje očitanih vrijednosti u integer tip
    servo.write(angle); // Ispis primljene vrijednosti na servo
    servo2.write(angle); // Ispis primljene vrijednosti na servo

    Serial.print("Servo angle: ");
    Serial.println(angle); // Ispis primljene vrijednosti 
    while (Serial.available()) {
      Serial.read(); // Čišćenje buffer-a
    }
  }



}
