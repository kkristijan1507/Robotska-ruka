/*   Version: 1.1.3  |  License: Apache 2.0  |  Author: JDWifWaf@gmail.com   */
#include "TCA9548A.h"

#define DEBUG 0  // Enable Debug Mode

/**
 * @brief                   Overloaded constructor with address setting
 *
 * @param bool address      I2C address of the device
 */
TCA9548A::TCA9548A(uint8_t address) : _address(address) {}

/**
 * @brief                   Function initializes I2C communication
 *
 * @param TwoWire* inWire   I2C handler
 */
void TCA9548A::begin(TwoWire &inWire)
{
    this->myWire = &inWire;
    this->myWire->begin();
}

/**
 * @brief                   Function that connects output channel to input
 *
 * @param uint8_t channel   Which channel to open
 */
void TCA9548A::openChannel(uint8_t channel)
{
    uint8_t buff = 0x00;    
    buff = 1 << channel;
    this->_channels |= buff;

    #if DEBUG
    Serial.print("Open Channel: "); Serial.print(channel); Serial.print(" Data: "); Serial.println(buff);
    #endif  

    write(this->_channels);
}

/**
 * @brief                   Function that disconnects output channel from input
 *
 * @param uint8_t channel   Which channel to close
 */
void TCA9548A::closeChannel(uint8_t channel)
{
    uint8_t buff = 0x00;    
    buff = 1 << channel;    
    this->_channels ^= buff;

    #if DEBUG
    Serial.print("Close Channel: "); Serial.print(channel); Serial.print(" Data: "); Serial.println(buff);
    #endif  

    write(this->_channels);
}


/**
 * @brief                   Function that disconnects all output channels frominput
 *
 * 
 */
void TCA9548A::closeAll()
{
    this->_channels = 0x00;
    write(this->_channels);
}

/**
 * @brief                   Function that connects all output channel to input
 *
 * 
 */
void TCA9548A::openAll()
{
    this->_channels = 0xFF;
    write(this->_channels);
}

/**
 * @brief                   Function that directly modifies channels register in TCA9548A
 *
 * @param uint8_t value     Which value to write in channels register
 */
void TCA9548A::writeRegister(uint8_t value)
{
    this->_channels = value;

    #if DEBUG
    Serial.print("Write Control Register: "); Serial.println(value);
    #endif  

    write(this->_channels);
}

/**
 * @brief                   Function that writes data in registers of TCA9548A
 *
 * @param uint8_t inData    Data to write
 */
void TCA9548A::write(uint8_t inData)
{
    #if DEBUG
    Serial.print("Write Address: "); Serial.print(this->_address, HEX); Serial.print(" Data: "); Serial.println(inData);
    #endif

    this->myWire->beginTransmission(this->_address);
    this->myWire->write(inData);
    this->myWire->endTransmission(true);
}

/**
 * @brief                   Function that reads registers from TCA9548A
 *
 * @return                  Returns buffer containing register data
 */
uint8_t TCA9548A::read()
{
    uint8_t buff = 0;
    this->myWire->requestFrom((uint16_t)this->_address, (uint8_t)1, (uint8_t)true);

    if(!this->myWire->available())
        return 255;

    buff = this->myWire->read();

    #if DEBUG
    Serial.print("Read Address: "); Serial.print(this->_address, HEX); Serial.print(" Data: "); Serial.println(buff);
    #endif
    
    return buff;
}
