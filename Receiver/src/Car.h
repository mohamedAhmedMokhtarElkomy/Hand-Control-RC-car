#include <Arduino.h>
#define CarRightForward PA12	 
#define CarRightBackward PA15

#define CarLeftForward PB3
#define CarLeftBackward PB4

#define CarLeftSpeed PA1 //ENA
#define CarRigthSpeed PA0 //ENB

#define SPEED_RATIO 0.7

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

int CarSpeed(int tilt, int ratioLeft = 1, int ratioRight = 1){
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
  analogWrite(CarLeftSpeed, PWM * ratioLeft); //ENA pin
  analogWrite(CarRigthSpeed,  PWM * ratioRight); //ENB pin
  return PWM;
}

//ratio used for horizontal and vertical direction combined
// int CarSpeed(int tilt , int ratioLeft = 1, int ratioRight = 1){
//   if(tilt<0)
//     tilt = -tilt;
//   int PWM = ((tilt - 1) * 30);
//   if(PWM > 255)
//     PWM = 255;
//   analogWrite(CarLeftSpeed, PWM * ratioLeft< 100? 100: PWM * ratioLeft); //ENA pin
//   analogWrite(CarRigthSpeed, PWM * ratioRight < 100? 100: PWM * ratioRight); //ENB pin
//   return PWM;
// }

	//100-->255
	//155/9 = 20
  //taking x and y and turning them to PWM
  //x and y Resolution 2-->10  (9 modes)
  //PWM Resolution 0-->255
  //Equation 255/9 = 28.3 ~= 30
  //0 0, 1 0, 2 100, 3 120, 4 140, 5 160, 6 180, 7 200, 8 220, 9 240, 10 255.
  //we only enter this function if left or right >1
  