//
//    FILE: ADS_read_async.ino
//  AUTHOR: Rob.Tillaart
// VERSION: 0.1.1
// PURPOSE: read analog inputs - asynchronous
//

// Used by Soldered EasyC board with minor additions

// test
// connect 1 potmeter per port.
//
// GND ---[   x   ]------ 5V
//            |
//
// measure at x (connect to AIN0).
//

#include "ADS1115-SOLDERED.h"

// Declare your ADS1115 instance:
ADS1115 ADS;
float f = 0;

void setup()
{
    // initialize the Serial comunication
    Serial.begin(115200);
    Serial.println(__FILE__);
    Serial.print("ADS1X15_LIB_VERSION: ");
    Serial.println(ADS1X15_LIB_VERSION);

    // setup the ADS1115
    ADS.begin();
    ADS.setGain(0);
    f = ADS.toVoltage(); // voltage factor
    ADS.requestADC(0);
}

void loop()
{
    // read the ADC value if available
    if (ADS.isBusy() == false)
    {
        int16_t val_0 = ADS.getValue();
        ADS.requestADC(0); // request a new one
        Serial.print("\tAnalog0: ");
        Serial.print(val_0);
        Serial.print('\t');
        Serial.println(val_0 * f, 3);
    }
    // simulate other tasks...
    delay(2000);
}

// -- END OF FILE --
