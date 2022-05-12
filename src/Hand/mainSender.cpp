// #include <Arduino.h>
// //NRF Lib
// #include <SPI.h>
// #include <nRF24L01.h>
// #include <RF24.h>
// //MPU Lib
// #include <Adafruit_MPU6050.h>
// #include <Adafruit_Sensor.h>
// #include <Wire.h>

// #define F 0
// #define R 1
// #define B 2
// #define L 3
// #define FL 4
// #define FR 5
// #define BR 6
// #define BL 7
// #define N 8


// //NRF Pins
// #define CE PB0// TODO common line
// #define CSN PA4// TODO common line

// //DEBUG Pins
// #define RX PA9// TODO common line
// #define TX PA10// TODO common line
// #define TESTLED PB9// TODO common line

// RF24 radio(CE, CSN);// TODO common line
// HardwareSerial serial(TX, RX);// TODO common line
// Adafruit_MPU6050 mpu;
// // TODO common line
// const byte address[6] = "00002";  //same Address used for both sender and receiver


// // F FL = E  FR = G
// // B BL = A BR = C
// // R
// // L
// struct messageData// TODO common line
// {
//   int direction = F;
//   int tilt = 0; //0 to 10 or 11
//   byte test = 5;

// };


// messageData message;

// void setup(){
//     serial.begin(9600);
//     serial.println("serial is ready");
    
//     setupMPU();
    
//     setupNRF();  
    
//     setupOnLED();


// }

// void loop(){
    
//     loopMPU();
//     serial.println("Sending message...");
//     sendMessage();
// }


// //MPU Functions
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
// 		if(x>1){
// 			serial.println("Backward Left");
//             message.direction = BL;
//             message.tilt =  x>y? x:y;

// 			serial.println(x,y);
//     		serial.println(PWM);
// 		}
// 		else if(x<-1){
// 			serial.println("Backward Right");
// 			message.direction = BR;
//             message.tilt =  x>y? x:y;
            
//             serial.println(x,y);
// 			serial.println(PWM);
// 		}
// 		else{
// 			serial.println("Backward");
// 			message.direction = B;
//             message.tilt =  y;
            
//             serial.println(y);
// 			serial.println(PWM);	
// 		}
// 	}
// 	else if(y < -1){
// 		serial.println(y);
// 		if(x>1){
// 			serial.println("Forward Left");
// 			message.direction = FL;
//             message.tilt =  x>y? x:y;
            
//             serial.println(x,y);
// 			serial.println(PWM);
// 		}
// 		else if(x<-1){
// 			serial.println("Forward Right");
//             message.direction = FR;
//             message.tilt =  x>y? x:y;
            
// 			serial.println(x,y);
// 			serial.println(PWM);
// 		}
// 		else{
// 			serial.println("Forward");
//             message.direction = F;
//             message.tilt =  x>y? x:y;
            
// 			serial.println(x,y);
// 			serial.println(PWM);	
// 		}
// 	}
// 	else if(x>1){
		
// 		serial.println("Left");
// 		message.direction = L;
//         message.tilt =  x;
            
// 		serial.println(x);
//         serial.println(PWM);
// 	}
// 	else if(x<-1){
		
// 		serial.println("Right");
//         message.direction = R;
//         message.tilt =  x;
            
// 		serial.println(x);
// 		serial.println(PWM);
// 	}
// 	else{
//         message.direction = N;
//         message.tilt =  0;
            

// 		serial.println("Idle");
//   }
// }



// //NRF FUNCTIONS

// // TODO common method
// void setupNRF()
// {
//   radio.begin();
//   radio.openWritingPipe(address);
//   radio.setPALevel(RF24_PA_MIN);
//   radio.stopListening();  //set nrf as transmitter
//   serial.println("NRF is ready");
  
// }

// void sendMessage()
// {  
//   if(sizeof(message) < 32){
//     radio.write(&message, sizeof(messageData));
//     serial.println("Message is sent");
//   }
//   else{
//     serial.println("Message size is greater than 32 bytes. current message size is:  ");
//     serial.println(sizeof(message));
//   }
//   delay(500);
// }
// // TODO common method
// void setupOnLED()
// {
//   pinMode(TESTLED, OUTPUT);
//   digitalWrite(TESTLED, HIGH);
// }