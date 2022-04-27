#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Car.h>

HardwareSerial serial(PA10, PA9);
Adafruit_MPU6050 mpu;

void setupMPU();

void loopMPU();

void checkDir(int x, int y, int z);

void setupCar();
void moveForward();
void moveBackward();
void moveRight();
void moveLeft();
void Idle();



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


void setupMPU(){
	// Try to initialize!
	if (!mpu.begin()) {
		serial.println("Failed to find MPU6050 chip");
		while (1) {
		  delay(10);
		}
	}
	serial.println("MPU6050 Found!");

	// set accelerometer range to +-8G
	mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

	// set gyro range to +- 500 deg/s
	mpu.setGyroRange(MPU6050_RANGE_500_DEG);

	// set filter bandwidth to 21 Hz
	mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  
	delay(100);
}

void loopMPU(){
	/* Get new sensor events with the readings */
	sensors_event_t a, g, temp;
	mpu.getEvent(&a, &g, &temp);
	checkDir(a.acceleration.x, a.acceleration.y, a.acceleration.z);
	delay(500);
}

void checkDir(int x, int y, int z){
	bool Horizontal = true;
	bool Vertical = true;
	
	if(x > 1){
		serial.println("Left");
		serial.println(x);
		moveLeft();
    int PWM = CarSpeed(x);
    serial.println(PWM);
	}
	else if(x < -1){
		serial.println("Right");
		serial.println(x);
		moveRight();
    int PWM = CarSpeed(x);
    serial.println(PWM);
	}
	// else
	//  Horizontal = false;
	
	else if(y > 1){
		serial.println("Backward");
		serial.println(y);
		moveBackward();
    int PWM = CarSpeed(y);
    serial.println(PWM);
	}
	else if(y < -1){
		serial.println("Forward");
		serial.println(y);
		moveForward();
    int PWM = CarSpeed(y);
    serial.println(PWM);
	}
	// else
	//  Vertical = false;

	// if(!Horizontal  && !Vertical)
	else{
		Idle();
    serial.println(x);
		serial.println(y);
  }
}

