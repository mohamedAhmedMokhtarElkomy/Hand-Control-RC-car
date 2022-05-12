// #include <Adafruit_MPU6050.h>
#include <Wire.h>
// #include <Adafruit_Sensor.h>
#include <Car.h>

#define SPEED_RATIO 0.7

// HardwareSerial serial(PA10, PA9);
// Adafruit_MPU6050 mpu;

void setupMPU();

void loopMPU();

void checkDir(int x, int y, int z);

void setupCar();
void moveForward();
void moveBackward();
void moveRight();
void moveLeft();
void Idle();

int PWM;

void setup(void) {
	//ON LED
	// pinMode(PA7, OUTPUT);
	// digitalWrite(PA7, HIGH);
	
	serial.begin(115200);
	// setupMPU();
	setupCar();	
	
  	analogWrite(CarLeftSpeed, 100); //ENA pin
  	analogWrite(CarRigthSpeed, 100); //ENB pin	
	PWM = CarSpeed(3);
}

void loop() {
	serial.println(PWM);
	// moveForward();
	// serial.println("Moving");
//   loopMPU();	
	moveForward();
	delay(5000);

	serial.println("Here");


}


// void setupMPU(){
// 	// Try to initialize!
// 	if (!mpu.begin()) {
// 		serial.println("Failed to find MPU6050 chip");
// 		while (1) {
// 		  delay(10);
// 		}
// 	}
// 	serial.println("MPU6050 Found!");

// 	// set accelerometer range to +-8G
// 	mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

// 	// set gyro range to +- 500 deg/s
// 	mpu.setGyroRange(MPU6050_RANGE_500_DEG);

// 	// set filter bandwidth to 21 Hz
// 	mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  
// 	delay(100);
// }

// void loopMPU(){
// 	/* Get new sensor events with the readings */
// 	sensors_event_t a, g, temp;
// 	mpu.getEvent(&a, &g, &temp);
// 	checkDir(a.acceleration.x, a.acceleration.y, a.acceleration.z);
// 	delay(500);
// }

// void checkDir(int x, int y, int z){
// 	bool Horizontal = true;
// 	bool Vertical = true;
// 	int PWM=0;

// 	if(y > 1){
// 		moveBackward();
// 		if(x>1){
// 			serial.println("Backward Left");
// 			serial.println(x,y);
// 			if(x>y)
// 				PWM = CarSpeed(x,SPEED_RATIO,1); //both wheels same speed
// 			else
// 				PWM = CarSpeed(y,SPEED_RATIO,1); //both wheels same speed
//     		serial.println(PWM);
// 		}
// 		else if(x<-1){
// 			serial.println("Backward Right");
// 			serial.println(x,y);
// 			if(x>y)
// 				PWM = CarSpeed(x,1,SPEED_RATIO); //both wheels same speed
// 			else
// 				PWM = CarSpeed(y,1,SPEED_RATIO); //both wheels same speed
//     		serial.println(PWM);
// 		}
// 		else{
// 			serial.println("Backward");
// 			serial.println(y);
// 			PWM = CarSpeed(y,1,1); //both wheels same speed
//     		serial.println(PWM);	
// 		}
// 	}
// 	else if(y < -1){
		
// 		moveForward();
// 		serial.println(y);
// 		if(x>1){
// 			serial.println("Forward Left");
// 			serial.println(x,y);
// 			if(x>y)
// 				PWM = CarSpeed(x,SPEED_RATIO,1); //both wheels same speed
// 			else
// 				PWM = CarSpeed(y,SPEED_RATIO,1); //both wheels same speed
//     		serial.println(PWM);
// 		}
// 		else if(x<-1){
// 			serial.println("Forward Right");
// 			serial.println(x,y);
// 			if(x>y)
// 				PWM = CarSpeed(x,1,SPEED_RATIO); //both wheels same speed
// 			else
// 				PWM = CarSpeed(y,1,SPEED_RATIO); //both wheels same speed
//     		serial.println(PWM);
// 		}
// 		else{
// 			serial.println("Forward");
// 			serial.println(x,y);
// 			if(x>y)
// 				PWM = CarSpeed(x,1,1); //both wheels same speed
// 			else
// 				PWM = CarSpeed(y,1,1); //both wheels same speed
//     		serial.println(PWM);	
// 		}
// 	}
// 	else if(x>1){
		
// 		serial.println("Left");
// 		serial.println(x);
// 		moveLeft();
// 		PWM = CarSpeed(x,1,1); //both wheels same speed
// 		serial.println(PWM);
// 	}
// 	else if(x<-1){
		
// 		serial.println("Right");
// 		serial.println(x);
// 		moveRight();
// 		PWM = CarSpeed(x,1,1); //both wheels same speed
// 		serial.println(PWM);
// 	}
// 	else{
// 		Idle();
// 		serial.println("Idle");
//   }
// }
