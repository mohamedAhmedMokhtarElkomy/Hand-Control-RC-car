#include <MPU.h>



void setup(void) {
	//ON LED
	// pinMode(PA7, OUTPUT);
	// digitalWrite(PA7, HIGH);
	
	serial.begin(115200);
	setupMPU();
	setupCar();		
}

void loop() {
  loopMPU();	
}




