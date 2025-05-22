//
//    FILE: ADS_continuous.ino
//  AUTHOR: Rob.Tillaart
// VERSION: 0.1.1
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


#include "ADS1015-SOLDERED.h"

// Declare an ADS1015 class instance.
ADS1015 ADS;

void setup()
{
    // Setup Serial
    Serial.begin(115200);
    Serial.println(__FILE__);
    Serial.print("ADS1X15_LIB_VERSION: ");
    Serial.println(ADS1X15_LIB_VERSION);

    // setup ADS1015
    ADS.begin();
    ADS.setGain(0);     // 6.144 volt
    ADS.setDataRate(7); // fast
    ADS.setMode(0);     // continuous mode
    ADS.readADC(0);     // first read to trigger
}

void loop()
{
    // read ADC
    Serial.println(ADS.getValue());
}

// -- END OF FILE --