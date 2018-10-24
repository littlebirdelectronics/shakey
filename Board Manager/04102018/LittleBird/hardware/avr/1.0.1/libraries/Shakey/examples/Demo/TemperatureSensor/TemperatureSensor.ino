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
 
#include <LittleBird_LM75A.h>

LittleBird_LM75A tempsensor;

void setup() {
	Serial.begin(9600);
	tempsensor.begin();
}

void loop() {
	// put your main code here, to run repeatedly:
	Serial.println(tempsensor.getCelsius());
	Serial.println(tempsensor.getFarenheit());
	delay(1000);
}
