/*************************************************** 
This is a library for the LittleBird Temperature Sensor LM75A

Designed specifically to work with the LittleBird Shakey
----> https://www.littlebirdelectronics.com.au/shakey

  
LittleBird invests time and resources providing this open source code, 
please support LittleBird and open-source hardware by purchasing 
products from LittleBird Electronics!

Written by JP Liew for Little Bird Electronics
BSD license, all text above must be included in any redistribution
****************************************************/

// This is a minimalist library returning just the temperature. 
// There are a other features for LM75A that will be progressively implemented.
 
#include <Wire.h>
#include "LittleBird_LM75A.h"

LittleBird_LM75A::LittleBird_LM75A()
{
	_i2cAddress = LM75A_DEFAULT_ADDRESS;
}

LittleBird_LM75A::LittleBird_LM75A(uint8_t i2cAddress)
{
	_i2cAddress = i2cAddress;
}

void LittleBird_LM75A::begin()
{
	Wire.begin();
}
	
void LittleBird_LM75A::end()
{
	Wire.end();
}
	
float LittleBird_LM75A::getCelsius()
{
	uint16_t i2cData=0;
	float temperature;
	
	Wire.beginTransmission(_i2cAddress);
	Wire.write(LM75A_REGISTER_TEMP);
	if(Wire.endTransmission()) {
		return LM75A_INVALID_TEMPERATURE;
	}
	
	if (Wire.requestFrom(_i2cAddress,(uint8_t)2)) {
		uint8_t msb = Wire.read();
		uint8_t lsb = Wire.read();
		
		i2cData = msb << 8 | lsb;
		i2cData = i2cData >>5;
		
		if (i2cData & 0x400) {
			// D10 bit 1, temperature is negative, need to do 2's complement
			i2cData = ~i2cData + 1;
			temperature = -1 * (float)i2cData * 0.125f;
		} else {
			temperature = (float)i2cData * 0.125f;
		}
	} else {
		return LM75A_INVALID_TEMPERATURE;
	}
	return temperature;
}
	
float LittleBird_LM75A::getFarenheit()
{
	return getCelsius() * 1.8f + 32.0f;
}



  