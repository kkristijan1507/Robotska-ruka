/**
 **************************************************
 *
 * @file        WriteRegister.ino
 * @brief       Advanced example of how to write to a TCA9548A I2C multiplexer register.
 *
 * Learn more about the board here: https://www.solde.red/333042
 *
 * @authors     JDWifWaf@gmail.com @ soldered.com
 * 
 *              Modified by soldered.com
 ***************************************************/

#include "TCA9548A-SOLDERED.h"
#include <Arduino.h>

TCA9548A I2CMux; // Address can be passed into the constructor

void setup()
{
    Serial.begin(115200); // Define baud rate

    //  Wire.setPins(21, 22);      // ESP32 users, use setPins(sda, scl) if customised, *before* passing Wire (default)
    //  to the library (the line below).
    I2CMux.begin();

    I2CMux.closeAll(); // Set a base state which we know (also the default state on power on)
}

void loop()
{
    uint8_t buff = 0x00;

    Serial.println("\n--- Calculate Channel Byte (153) ---");

    delay(500);

    Serial.println("Adding Channels 0, 3, 4 & 7");
    buff |= TCA_CHANNEL_0;
    buff |= TCA_CHANNEL_3;
    buff |= TCA_CHANNEL_4;
    buff |= TCA_CHANNEL_7;  //Enable channels in buf variable

    delay(500);

    Serial.print("Writing Register: ");
    Serial.println(buff);
    I2CMux.writeRegister(buff); //Write buf variable to register

    delay(500);

    Serial.print("Reading Register: ");
    Serial.println(I2CMux.readRegister());  //Read data from register

    delay(500);

    Serial.println("Closing Channels");
    I2CMux.closeAll();

    while (1 == 1)
        ;
}