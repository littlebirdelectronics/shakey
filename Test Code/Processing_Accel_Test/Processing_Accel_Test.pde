import processing.serial.*;

Serial myPort;        // The serial port
int xPos = 1;         // horizontal position of the graph
float XinByte = 0;
float YinByte = 0;
float ZinByte = 0;

int  br=0;
boolean ready;
float x, y, z;
float XprevY=height;
float XprevX=0;

float YprevY=height;
float YprevX=0;

float ZprevY=height;
float ZprevX=0;

void setup () {
	// set the window size:
	size(400, 300);

	// List all the available serial ports
	printArray(Serial.list());
	myPort = new Serial(this, "COM82", 115200);

	// don't generate a serialEvent() unless you get a newline character:
	myPort.bufferUntil('\n');
	
	// set initial background:
	background(0);
}

void draw () {
	// draw the line:
	stroke(255,0,0);    // Red Line for X 
	line(XprevX, XprevY, xPos, height - XinByte);

	stroke(0, 255, 0);  // Green Line for Y 
	line(YprevX, YprevY, xPos, height - YinByte);

	stroke(0, 0, 255);  // Blue Line for Z
	line(ZprevX, ZprevY, xPos, height - ZinByte);
	
	XprevY= height - XinByte;
	XprevX=xPos;
	
	YprevY= height - YinByte;
	YprevX=xPos;

	ZprevY= height - ZinByte;
	ZprevX=xPos;
	
	// at the edge of the screen, go back to the beginning:
	if (xPos >= width) {
		xPos = 0;
		XprevX=0;
		YprevX=0;
		ZprevX=0;
		background(0);
	} else {
		// increment the horizontal position:
		xPos++;
	}
}

void serialEvent (Serial myPort) {
	// get the ASCII string:
	String str = myPort.readStringUntil('\n');  
	if(str.charAt(0) == 'p') {ready = true; println("ready");br=0;}
	else if (br == 0){ 
		x = float(str); 
		br++; 
		XinByte=map(x,-2,2,0, height); 
		println(x); 
	}
	else if (br == 1){ 
		y = float(str); 
		br++;
		YinByte=map(y,-2,2,0, height); 
		println(y);
	}
	else if (br == 2){ 
		z = (-1)*float(str);
		br=0;
		ZinByte=map(z,-2,2,0, height); 
		println(z);
	}  
	redraw(); 
}
