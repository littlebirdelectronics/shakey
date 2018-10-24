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
 
#include <LittleBird_ICM20689.h>

LittleBird_ICM20689 motionsensor;

void setup() {
	Serial.begin(9600);
	motionsensor.begin();
}

void loop() {
	if (motionsensor.whoami()==0x98) {
		Serial.print("ICM20689 found at I2C address 0x");
		Serial.println(motionsensor.getAddress(),HEX);
	}
	delay(2000);
}
