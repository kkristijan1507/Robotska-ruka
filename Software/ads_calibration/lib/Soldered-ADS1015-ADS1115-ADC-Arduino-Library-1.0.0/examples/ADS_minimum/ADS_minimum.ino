//
//    FILE: ADS_minimum.ino
//  AUTHOR: Rob.Tillaart
// VERSION: 0.1.0
// PURPOSE: read analog input
//

// Used by Soldered EasyC board with minor additions

// test
// connect 1 potmeter
//
// GND ---[   x   ]------ 5V
//            |
//
// measure at x (connect to AIN0).

// view with Serial Plotter

#include "ADS1115-SOLDERED.h" // or #include "ADS1015-SOLDERED.h"

// choose you sensor
// ADS1015 ADS;
ADS1115 ADS;

void setup()
{
    // Initialize the Serial communication
    Serial.begin(115200);
    Serial.println(__FILE__);
    Serial.print("ADS1X15_LIB_VERSION: ");
    Serial.println(ADS1X15_LIB_VERSION);

    // initialize the sensor
    ADS.begin();
    ADS.setGain(0); // 6.144 volt
    Serial.println("Voltage");
}

void loop()
{
    //  read the value
    int16_t raw = ADS.readADC(0);
    Serial.println(ADS.toVoltage(raw), 3);
}

// -- END OF FILE --
