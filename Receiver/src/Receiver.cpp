#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include <Car.h>

#define CE PB0// TODO common line
#define CSN PA4// TODO common line

#define RX PA9// TODO common line
#define TX PA10// TODO common line
RF24 radio(CE, CSN);

#define SPEED_RATIO 0.7

HardwareSerial serial(TX, RX);// TODO common line

const byte address[6] = "00002";

void moveCar();
bool enterFunc = false;

struct messageData
{
  int direction;
  int tilt;
  byte test;

};

messageData message;

void setupNRF();
void receiveMessage();

void setup() {
  serial.begin(9600);
  serial.println("Receiver is ON");
  
  setupNRF();
  setupCar();

  serial.println("Setup is done");
  Idle();
}

void loop() {
  
  // moveForward();
  // delay(5000);
  // delay(100);
  receiveMessage();
  moveCar();
  // moveBackward();
}

void setupNRF()
{
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  
}

void receiveMessage()
{
  if (radio.available()) {
    serial.println("received");
    radio.read(&message, sizeof(messageData));
    serial.print("Direction:");
    serial.println(message.direction);
    serial.print("tilt:");
    serial.println(message.tilt);
  }
  else{
    serial.println("radio failed");
  }
  // delay(500);
}

void moveCar(){
  
  switch(message.direction){
    case 0://Forward
      moveForward();
      CarSpeed(message.tilt);
      break;
    case 1://Right
      moveRight();
      CarSpeed(message.tilt);
      break;
    case 2://Backward
      moveBackward();
      CarSpeed(message.tilt);
      break;
    case 3://Left
      moveLeft();
      CarSpeed(message.tilt);
      break;
    case 4://Forward Left
      moveForward();
      CarSpeed(message.tilt, SPEED_RATIO,1);
      break;
    case 5://Forward Right
      moveForward();
      CarSpeed(message.tilt, 1,SPEED_RATIO);
      break;
    case 6://Backward Right 
      moveBackward();
      CarSpeed(message.tilt, 1,SPEED_RATIO);
      break;
    case 7://Backward Left
      moveBackward();
      CarSpeed(message.tilt, SPEED_RATIO,1);
      break;
    default://Idle in case 8 or any
      Idle();
      break;
  }


}