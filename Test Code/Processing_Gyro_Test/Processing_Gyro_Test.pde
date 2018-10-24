import processing.serial.*; 
Serial myPort; 

void setup()  {
	size(640, 360, P3D);  
	myPort = new Serial(this, "COM78", 115200); 
	myPort.bufferUntil('\n');
}

float x, y, z;
float angle_x = 0, angle_y = 0, angle_z = 0;
int  br=0;
boolean ready;

void draw()
{ 
	fill(230);  
	background(200); 
	lights();  
	translate(width/2, height/2, 0);  
	rotateX(angle_x); 
	rotateY(angle_z);
	rotateZ(angle_y);  
	box(160,70,120);
}

void serialEvent (Serial myPort)  
{
	String str = myPort.readStringUntil('\n');  
	if(str.charAt(0) == 'p') {ready = true; println("ready"); br=0;}
	else if (br == 0){ x = float(str); br++;  angle_x += x/800; println(x);}
	else if (br == 1){ y = float(str); br++;  angle_y += y/800; println(y);}
	else if (br == 2){ z = (-1)*float(str); br = 0; angle_z += z/800;println(z);}  

	redraw(); 
}
