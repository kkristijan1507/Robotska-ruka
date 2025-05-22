/**
 **************************************************
 *
 * @file        BasicUsage.ino
 * @brief       Basic usage example.
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
    Serial.begin(115200);   //Start serial communication with PC

    //  Wire.setPins(21, 22);       // ESP32 users, use setPins(sda, scl) if customised, *before* passing Wire to the
    //  library (the line below).
    I2CMux.begin(); // Wire instance is passed to the library

    I2CMux.closeAll(); // Set a base state which we know (also the default state on power on)
}

void loop()
{
    I2CMux.openChannel(0);
    /* Code to interactive with revealed address on bus */
    I2CMux.closeChannel(0);

    I2CMux.openChannel(1);
    I2CMux.openChannel(2);
    /* Code  to interactive with revealed addresses on bus */
    I2CMux.closeAll();
}