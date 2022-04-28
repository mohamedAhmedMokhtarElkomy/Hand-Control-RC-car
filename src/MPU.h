#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Car.h>

#define SPEED_RATIO 0.7



Adafruit_MPU6050 mpu;

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

void checkDir(int x, int y, int z){
	int Horizontal = (x < -1 || x > 1) ? true : false;
	bool Vertical = (y < -1 || y > 1) ? true : false;
	int PWM=0;
    int ratioLeft = 1;
    int ratioRight = 1;

	if(y > 1){
		moveBackward();
		if(x>1){
			serial.println("Backward Left");
			ratioLeft = SPEED_RATIO;
            serial.println(x,y);
			
		}
		else if(x<-1){
			serial.println("Backward Right");
            ratioRight = SPEED_RATIO;
		}
		else
			serial.println("Backward");	
	}
	else if(y < -1){
		
		moveForward();
		if(x>1){
			serial.println("Forward Left");
            ratioLeft = SPEED_RATIO;
		}
		else if(x<-1){
			serial.println("Forward Right");
            ratioRight = SPEED_RATIO;
		}
		else
			serial.println("Forward");
	}

	else if(x>1){
		serial.println("Left");
		moveLeft();
	}
	else if(x<-1){
		serial.println("Right");
		moveRight();
	}
	else{
		serial.println("Idle");
		Idle();
    }

    PWM = CarSpeed(x>y? x:y,ratioLeft,ratioRight);
    serial.println(PWM);
    x!=NULL? serial.println(x): NULL;
    y!=NULL? serial.println(y) : NULL;
    
}

void loopMPU(){
	/* Get new sensor events with the readings */
	sensors_event_t a, g, temp;
	mpu.getEvent(&a, &g, &temp);
	checkDir(a.acceleration.x, a.acceleration.y, a.acceleration.z);
	delay(500);
}

