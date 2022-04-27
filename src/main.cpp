#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#define CarRightForward PB11 
#define CarRightBackward PB10

#define CarLeftForward PB1 
#define CarLeftBackward PB0 

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
	pinMode(PA7, OUTPUT);
	digitalWrite(PA7, HIGH);
	
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
	/* Print out the values */
	// serial.print("Acceleration X: ");
	// serial.print(a.acceleration.x);
	// serial.print(", Y: ");
	// serial.print(a.acceleration.y);
	// serial.print(", Z: ");
	// serial.print(a.acceleration.z);
	// serial.println(" m/s^2");
	// serial.print("Rotation X: ");
	// serial.print(g.gyro.x);
	// serial.print(", Y: ");
	// serial.print(g.gyro.y);
	// serial.print(", Z: ");
	// serial.print(g.gyro.z);
	// serial.println(" rad/s");
	// serial.print("Temperature: ");
	// serial.print(temp.temperature);
	// serial.println(" degC");
	// serial.println("");
	delay(500);
}

void checkDir(int x, int y, int z){
	bool Horizontal = true;
	bool Vertical = true;
	
	if(x > 1){
		serial.println("Left");
		moveLeft();
	}
	else if(x < -1){
		serial.println("Right");
		moveRight();
	}
	// else
	//  Horizontal = false;
	
	else if(y > 1){
		serial.println("Backward");
		moveBackward();
	}
	else if(y < -1){
		serial.println("Forward");
		moveForward();
	}
	// else
	//  Vertical = false;

	// if(!Horizontal  && !Vertical)
	else
		Idle();


}

void setupCar(){
	pinMode(CarRightForward, OUTPUT);
	pinMode(CarRightBackward, OUTPUT);
	pinMode(CarLeftForward, OUTPUT);
	pinMode(CarLeftBackward, OUTPUT);

	digitalWrite(CarRightForward, LOW);
	digitalWrite(CarRightBackward, LOW);
	digitalWrite(CarLeftForward, LOW);
	digitalWrite(CarLeftBackward, LOW);
}

void moveForward()
{
	digitalWrite(CarRightForward, HIGH);
	digitalWrite(CarRightBackward, LOW);
	digitalWrite(CarLeftForward, HIGH);
	digitalWrite(CarLeftBackward, LOW);
}
void moveBackward()
{
	digitalWrite(CarRightForward, LOW);
	digitalWrite(CarRightBackward, HIGH);
	digitalWrite(CarLeftForward, LOW);
	digitalWrite(CarLeftBackward, HIGH);
}
void moveRight()
{
	digitalWrite(CarRightForward, HIGH);
	digitalWrite(CarRightBackward, LOW);
	digitalWrite(CarLeftForward, LOW);
	digitalWrite(CarLeftBackward, HIGH);
}
void moveLeft()
{
	digitalWrite(CarRightForward, LOW);
	digitalWrite(CarRightBackward, HIGH);
	digitalWrite(CarLeftForward, HIGH);
	digitalWrite(CarLeftBackward, LOW);
}
void Idle()
{
	digitalWrite(CarRightForward, LOW);
	digitalWrite(CarRightBackward, LOW);
	digitalWrite(CarLeftForward, LOW);
	digitalWrite(CarLeftBackward, LOW);
}