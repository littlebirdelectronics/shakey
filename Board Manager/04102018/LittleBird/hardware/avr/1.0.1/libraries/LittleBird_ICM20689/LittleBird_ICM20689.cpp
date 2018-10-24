/*************************************************** 
This is a library for the LittleBird ICM-20689 MEMS Motion Tracking Device

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
#include "LittleBird_ICM20689.h"

LittleBird_ICM20689::LittleBird_ICM20689()
{
	_i2cAddress = ICM20689_DEFAULT_ADDRESS;
}

LittleBird_ICM20689::LittleBird_ICM20689(uint8_t i2cAddress)
{
	_i2cAddress = i2cAddress;
}

void LittleBird_ICM20689::begin()
{
	Wire.begin();
	
	/*
    setClockSource(MPU6050_CLOCK_PLL_XGYRO);
    setFullScaleGyroRange(MPU6050_GYRO_FS_250);
    setFullScaleAccelRange(MPU6050_ACCEL_FS_2);
    setSleepEnabled(false); // thanks to Jack Elston for pointing this one out!
	*/
	
	
	
}
	
void LittleBird_ICM20689::end()
{
	Wire.end();
}

uint8_t LittleBird_ICM20689::whoami() 
{
	Wire.beginTransmission(_i2cAddress);
	Wire.write(ICM20689_WHO_AM_I);
	Wire.endTransmission();

	if (Wire.requestFrom(_i2cAddress,(uint8_t)1)) {
		return Wire.read();
	} else {
		return 0xff;
	}
}

uint8_t LittleBird_ICM20689::getAddress()
{
	return _i2cAddress;
}

uint16_t LittleBird_ICM20689::getGyroX()
{
	Wire.beginTransmission(_i2cAddress);
	Wire.write(ICM20689_GYRO_XOUT_H);
	Wire.endTransmission();
	
	Wire.requestFrom(_i2cAddress,(uint8_t)1);
	uint8_t highbyte = Wire.read();
	
	Wire.beginTransmission(_i2cAddress);
	Wire.write(ICM20689_GYRO_XOUT_L);
	Wire.endTransmission();
	
	Wire.requestFrom(_i2cAddress,(uint8_t)1);
	uint8_t lowbyte = Wire.read();
	
	return highbyte <<8 | lowbyte;

}

uint8_t LittleBird_ICM20689::getPowerManagement1()
{
	Wire.beginTransmission(_i2cAddress);
	Wire.write(ICM20689_PWR_MGMT_1);
	Wire.endTransmission();
	
	Wire.requestFrom(_i2cAddress,(uint8_t)1);
	uint8_t data = Wire.read();
	
	return data;
	
}

void LittleBird_ICM20689::setSleep(bool sleep) 
{
	uint8_t powermgt = getPowerManagement1();
	
	Serial.print("Before  ");
	Serial.println(powermgt,BIN);
	
	if (sleep) {
		// set to sleep
		Serial.println("Set Sleep");
		powermgt |= _BV(1<<6);
	} else {
		// wake up
		Serial.println("Set Wake");
		powermgt &=~_BV(1<<6);
	}

	Serial.print("Between ");
	Serial.println(powermgt,BIN);
	
	
	Wire.beginTransmission(_i2cAddress);
	Wire.write(ICM20689_PWR_MGMT_1);
	Wire.write(powermgt);
	Wire.endTransmission();
	
	powermgt = getPowerManagement1();
	Serial.print("After   ");
	Serial.println(powermgt,BIN);

}
