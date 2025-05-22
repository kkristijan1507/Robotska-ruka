//
//    FILE: ADS_async_8_channel.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo reading two ADS1115 modules in parallel
//    DATE: 2021-07-05
//     URL: https://github.com/RobTillaart/ADS1X15

// Used by Soldered EasyC board with minor additions

// Note all IO with the sensors are guarded by an isConnected()
// this is max robust, in non critical application one may either
// cache the value or only verify it in setup (least robust).
// Less robust may cause the application to hang - watchdog reset ?


#include "ADS1115-SOLDERED.h"

// ADS1115 default address: 0x48
ADS1115 ADS;

// Array to store sensor readings
int16_t val0[4] = {0, 0, 0, 0};

// Variables for example functions
int idx = 0;
uint32_t lastTime = 0;

void setup()
{
    // Initialize the Serial
    Serial.begin(115200);
    Serial.println(__FILE__);
    Serial.print("ADS1X15_LIB_VERSION: ");
    Serial.println(ADS1X15_LIB_VERSION);

    // Initialize the ADS1115
    ADS.begin();

    Serial.println(ADS.isConnected());

    ADS.setDataRate(4); // 7 is fastest, but more noise

    idx = 0;
    ADS_request_all();
}


void loop()
{
    // wait until all is read...
    while (ADS_read_all())
        ;

    // we have all 8 values
    ADS_print_all();

    delay(1000); // wait a second.
    ADS_request_all();
}

// Request all values from all sensors
void ADS_request_all()
{
    if (ADS.isConnected())
        ADS.requestADC(idx);
}


bool ADS_read_all()
{
    if (ADS.isConnected() && ADS.isBusy())
        return true;

    if (ADS.isConnected())
        val0[idx] = ADS.getValue();

    idx++;
    if (idx < 4)
    {
        ADS_request_all();
        return true;
    }
    idx = 0;
    return false;
}


// Print all data to Serial
void ADS_print_all()
{
    uint32_t now = millis();
    Serial.println(now - lastTime);
    lastTime = now;

    // PRINT ALL VALUES OF ADC0
    for (int i = 0; i < 4; i++)
    {
        Serial.print(val0[i]);
        Serial.print("\t");
    }
}

// -- END OF FILE --
