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

#ifndef LITTLEBIRD_LM75A_H
#define LITTLEBIRD_LM75A_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define LM75A_DEFAULT_ADDRESS		0x48		// Default LM75A Address, if A0-A2 are grounded
#define LM75A_REGISTER_TEMP			0			// Temperature register (read-only)
#define LM75A_REGISTER_CONFIG		1			// Configuration register (R/W)
#define LM75A_REGISTER_THYST		2			// Hysterisis register (R/W)
#define LM75A_REGISTER_TOS			3			// OS register (R/W)

#define LM75_CONF_OS_COMP_INT		1			// OS operation mode selection
#define LM75_CONF_OS_POL			2			// OS polarity selection
#define LM75_CONF_OS_F_QUE			3			// OS fault queue programming

#define LM75A_INVALID_TEMPERATURE	-1000.0f

class LittleBird_LM75A
{
	uint8_t	_i2cAddress;
	

public:
	LittleBird_LM75A();
	LittleBird_LM75A(uint8_t address);
	
	void begin();
	void end();
	
	float getCelsius();
	float getFarenheit();
	
};
#endif