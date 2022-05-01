#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE 7
#define CSN 8

RF24 radio(CE, CSN);

const byte address[6] = "00002";

struct messageData
{
  char direction;
  float PWM;
  byte test;

};

messageData message;

void setupNRF();
void receiveMessage();

void setup() {
  Serial.begin(9600);
  Serial.println("Receiver is ON");
  
  setupNRF();

  Serial.println("Setup is done");
}

void loop() {
  receiveMessage();
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
    Serial.println("received");
    radio.read(&message, sizeof(messageData));
    Serial.print("PWM:");
    Serial.println(message.direction);
  }
  else
    Serial.println("radio failed");
  delay(500);
}