#include <LittleBird_ICM20689.h>
#include <LittleBird_LM75A.h>
LittleBird_LM75A tempsensor;
LittleBird_ICM20689 motion;

#define TESTSWITCH A4

bool HasFailed = false;
bool Passed=false;

double ThreeHighLimit = 3.6;
double ThreeLowLimit = 3.0;
double TP1Volt=0;

long DelayCount=0;
bool toggle=LOW;
bool TestNow=false;

int pins[]={A5,A4,A3,A2,A1,A0,A6,A11,A8,A7};
char *pinsname[]={"A5","A4","A3","A2","A1","A0","A6","A11","A8","A7"};

bool TestPins(uint8_t OutP, uint8_t InP) {
	pinMode(OutP, OUTPUT);
	pinMode(InP, INPUT);
	
	digitalWrite(OutP, HIGH);
	delay(1);
	if (digitalRead(InP)==LOW) {
		Serial.print(OutP);
		Serial.print(",");
		Serial.print(InP);
		Serial.println(" FAILED!");
		HasFailed=true;
		return false;
	}

	digitalWrite(OutP, LOW);
	delay(1);
	if (digitalRead(InP)==HIGH) {
		Serial.print(OutP);
		Serial.print(",");
		Serial.print(InP);
		Serial.println(" FAILED!");
		HasFailed=true;
		return false;
	}
	
	Serial.println("Ok.");	
	return true;
}

void setup() {
	// put your setup code here, to run once:
	Serial.begin(115200);
	pinMode(LED_BUILTIN_TX, OUTPUT);
	pinMode(LED_BUILTIN_RX, OUTPUT);
	digitalWrite(LED_BUILTIN_TX,HIGH);
	digitalWrite(LED_BUILTIN_RX,HIGH);
	//pinMode(TESTSWITCH, INPUT_PULLUP);

}

void loop() {
	
	if (HasFailed) {
		DelayCount++;
		if (DelayCount>=7000) {
			toggle = !toggle;
			digitalWrite(LED_BUILTIN_TX, toggle);
			digitalWrite(LED_BUILTIN_RX, toggle);
			DelayCount=0;
		}
		//delay(100);
	} 

	if (Passed) {
		DelayCount++;
		if (DelayCount>=120000) {
			toggle = !toggle;
			digitalWrite(LED_BUILTIN_TX, toggle);
			digitalWrite(LED_BUILTIN_RX, toggle);
			DelayCount=0;
		}
	}	

	if (digitalRead(TESTSWITCH)==0) {
		delay(50);
		if (digitalRead(TESTSWITCH)==0) {
			while(digitalRead(TESTSWITCH)==0);
			TestNow=true;
		}
	}

	// Do Test
	if (TestNow) {
		TestNow=false;
		HasFailed=false;
		Passed=false;
		
		Serial.println("Shakey Factory Tests - 2019 Little Bird Electronics");
		Serial.println();
		delay(200);

		Serial.print("TEST 1 - ");
		TP1Volt=(double)5/1024 * analogRead(A5);
		if ((TP1Volt<ThreeHighLimit) && (TP1Volt>ThreeLowLimit)) {
			Serial.println ("Ok.");
		} else {
			Serial.print("+3.3V = ");
			Serial.print(TP1Volt);
			Serial.println (" FAILED!!!");
			HasFailed=true;
		}

		Serial.print("TEST 2 - ");
		TestPins(A3,A2);

		Serial.print("TEST 3 - ");
		TestPins(A1,1);
		
		Serial.print("TEST 4 - ");
		TestPins(A0,0);

		Serial.print("TEST 5 - ");
		TestPins(5,4);

		Serial.print("TEST 6 - ");
		TestPins(12,13);

		Serial.print("TEST 7 - ");
		TestPins(8,15);

		Serial.print("TEST 8 - ");
		TestPins(7,6);
		
		Serial.print("TEST 9 - ");
		tempsensor.begin();
		double temp=tempsensor.getCelsius();
		Serial.print(temp);
		Serial.print("C");
		if ((temp>20) && (temp<30)) {
			Serial.println(" Ok.");
		} else {
			Serial.println(" FAILED!");
			HasFailed=true;
		}
		

		Serial.print("TEST 10 - ");
		motion.begin();

		if (motion.whoami()==0x98) {
			Serial.println("0x98 Ok.");

			Serial.print("TEST 11 - ");
			motion.init();
			motion.calibrate();

			double gX,gY,gZ;
			
			gX=motion.getGyroX();
			Serial.print(gX);
			Serial.print(",");
			gY=motion.getGyroY();
			Serial.print(gY);
			Serial.print(",");
			gZ=motion.getGyroZ();
			Serial.print(gZ);
			
			if ( ((gX<0.5) && (gX>-0.5)) && ((gY<0.5) && (gY>-0.5)) && ((gZ<0.5) && (gZ>-0.5))) {
				Serial.println(" Ok.");
			} else {
				Serial.println(" FAILED!");
				HasFailed=true;
			}
		}
		
		
		int pincount = sizeof(pins)/sizeof(pins[0]);
		for (int i=0;i<pincount;i++) {
			pinMode(pins[i], INPUT);
			delay(5);
		}
		pinMode(5, INPUT);
		pinMode(1, INPUT);
		pinMode(0, INPUT);
		pinMode(13, INPUT);
		pinMode(15, INPUT);
		pinMode(7, INPUT);
		delay(100);
		
		for (int i=0;i<pincount;i++) {
			Serial.print("Voltage Pin ");
			Serial.print(pinsname[i]);
			Serial.print(" -\t");
			double Volt=(double)5/1024 * analogRead(pins[i]);
			Volt=(double)5/1024 * analogRead(pins[i]);
			delay(1);
			Volt=(double)5/1024 * analogRead(pins[i]);
			delay(1);
			Volt=(double)5/1024 * analogRead(pins[i]);
			delay(1);
			Volt=(double)5/1024 * analogRead(pins[i]);
			delay(1);
			Volt=(double)5/1024 * analogRead(pins[i]);
			delay(1);
			Volt=(double)5/1024 * analogRead(pins[i]);
			delay(1);
			Volt=(double)5/1024 * analogRead(pins[i]);
			Serial.println(Volt);
		}
		
		Serial.println();
		if (HasFailed) {
			Serial.println("WARNING!!! Board FAILED!!!");
			Serial.println();
		} else {
			Passed=true;
			Serial.println("Board PASSED.");
			Serial.println();
		}		
	}
	

}
