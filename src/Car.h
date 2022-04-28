#include <Arduino.h>
#define CarRightForward PB11 
#define CarRightBackward PB10

#define CarLeftForward PB1 
#define CarLeftBackward PB0


#define CarLeftSpeed PA7 //ENA
#define CarRigthSpeed PA6 //ENB

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

//ratio used for horizontal and vertical direction combined
int CarSpeed(int tilt, int ratioLeft, int ratioRight){
  if(tilt<0)
    tilt = -tilt;
  int PWM = ((tilt - 1) * 20) +100;
  if(PWM > 255)
    PWM = 255;
  analogWrite(CarLeftSpeed, PWM * ratioLeft< 100? 100: PWM * ratioLeft); //ENA pin
  analogWrite(CarRigthSpeed, PWM * ratioRight < 100? 100: PWM * ratioRight); //ENB pin
  return PWM;
}

	//100-->255
	//155/9 = 20
  //taking x and y and turning them to PWM
  //x and y Resolution 2-->10  (9 modes)
  //PWM Resolution 0-->255
  //Equation 255/9 = 28.3 ~= 30
  //0 0, 1 0, 2 100, 3 120, 4 140, 5 160, 6 180, 7 200, 8 220, 9 240, 10 255.
  //we only enter this function if left or right >1
  