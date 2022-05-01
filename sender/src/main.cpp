#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE PB0// TODO common line
#define CSN PA4// TODO common line
#define RX PA9// TODO common line
#define TX PA10// TODO common line
#define TESTLED PB9// TODO common line

RF24 radio(CE, CSN);// TODO common line
HardwareSerial serial(TX, RX);// TODO common line

// TODO common line
const byte address[6] = "00002";  //same Address used for both sender and receiver

void setupNRF();// TODO common line
void sendMessage(char dir);
void setupOnLED();// TODO common line
struct messageData// TODO common line
{
  char direction = 'r';
  float PWM = 10;
  byte test = 5;

};

messageData message;
void setup() {

  
  serial.begin(9600);
  serial.println("serial is ready");
  
  setupNRF();  

  setupOnLED();
  
}

void loop() {
  serial.println("Sending message...");
  sendMessage('f');
  

}
// TODO common method
void setupNRF()
{
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();  //set nrf as transmitter
  serial.println("NRF is ready");
  
}

void sendMessage(char dir)
{  
  
  message.direction = dir;
  if(sizeof(message) < 32){
    radio.write(&message, sizeof(messageData));
    serial.println("Message is sent");
  }
  else{
    serial.print("Message size is greater than 32 bytes. current message size is:  ");
    serial.println(sizeof(message));
  }
  delay(500);
}
// TODO common method
void setupOnLED()
{
  pinMode(TESTLED, OUTPUT);
  digitalWrite(TESTLED, HIGH);
}