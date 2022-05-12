#include <Arduino.h>

HardwareSerial serial(PA10, PA9);

#define CarRightForward PA12	 
#define CarRightBackward PA15

#define CarLeftForward PB3
#define CarLeftBackward PB4


#define CarLeftSpeed PA1 //ENA
#define CarRigthSpeed PA0 //ENB

void setupCar(){
	pinMode(CarRightForward, OUTPUT);
	pinMode(CarRightBackward, OUTPUT);
	pinMode(CarLeftForward, OUTPUT);
	pinMode(CarLeftBackward, OUTPUT);

  pinMode(CarLeftSpeed, OUTPUT);
  pinMode(CarRigthSpeed, OUTPUT);
  

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

int CarSpeed(int tilt){
  //taking x and y and turning them to PWM
  //x and y Resolution 2-->10  (9 modes)
  //PWM Resolution 0-->255
  //Equation 255/9 = 28.3 ~= 30
  //0 0, 1 0, 2 30, 3 60, 4 90, 5 120, 6 150, 7 180, 8 210, 9 240, 10 255.
  //we only enter this function if left or right >1
  if(tilt<0)
    tilt = -tilt;
  int PWM = (tilt - 1) * 30;
  if(PWM > 255)
    PWM = 255;
  analogWrite(CarLeftSpeed, PWM); //ENA pin
  analogWrite(CarRigthSpeed, PWM); //ENB pin
  return PWM;
}