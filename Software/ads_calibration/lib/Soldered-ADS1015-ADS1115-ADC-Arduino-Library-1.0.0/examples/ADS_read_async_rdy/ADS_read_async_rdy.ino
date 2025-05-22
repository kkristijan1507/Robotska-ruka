//
//    FILE: ADS_read_async_rdy.ino
//  AUTHOR: Rob.Tillaart
// VERSION: 0.1.1
// PURPOSE: read analog inputs - straightforward.
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

// EXPERIMENTAL
//
// The RDY pin (or ALERT Pin) is triggered when conversion is ready
//

#include "ADS1115-SOLDERED.h"

// Declare your ADC object:
ADS1115 ADS;
float f = 0;

void setup()
{
    // Initialize the Serial communication
    Serial.begin(115200);
    Serial.println(__FILE__);
    Serial.print("ADS1X15_LIB_VERSION: ");
    Serial.println(ADS1X15_LIB_VERSION);

    // initialize the ADC
    ADS.begin();
    ADS.setGain(0);      // 6.144 volt
    ADS.setDataRate(0);  // slow so the led blinks visible for the eye.
    f = ADS.toVoltage(); // voltage factor
    ADS.requestADC(0);

    // set the thresholds to Trigger RDY pin
    ADS.setComparatorThresholdLow(0x0000);
    ADS.setComparatorThresholdHigh(0x0200);
    ADS.setComparatorQueConvert(0); // enable RDY pin !!
    ADS.setComparatorLatch(0);
}

void loop()
{
    // read the ADC
    if (ADS.isReady())
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
