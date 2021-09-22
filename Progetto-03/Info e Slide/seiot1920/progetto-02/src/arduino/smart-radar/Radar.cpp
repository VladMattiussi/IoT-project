#include "Radar.h"
#include "Arduino.h"
#include "Led.h"
#include "servo_motor_impl.h"

Radar::Radar(int echoPin, int trigPin, int servoPin){
  pSonar = new Sonar(echoPin, trigPin);
  pServo = new ServoMotorImpl(servoPin);
  pServo->on();
}

void Radar::calibrate(){
  pServo->setPosition(0);
}

void Radar::selfTest(){
  for (int i = 0; i < 180; i+=10){
    pServo->setPosition(i);
    delay(200);
  }
  for (int i = 180; i > 0; i-=10){
    pServo->setPosition(i);
    delay(200);
  }
}

void Radar::rotateLeft(float delta){
  currentPosition -= delta;
  if (currentPosition < 0){
     currentPosition = 0;
  }
  pServo->setPosition((int) currentPosition);
}

void Radar::rotateRight(float delta){
  currentPosition += delta;
  if (currentPosition > 180){
     currentPosition = 180;
  }
	pServo->setPosition((int) currentPosition);
}

void Radar::setPos(float angle){
  currentPosition = angle;
  pServo->setPosition((int) angle);
}

float  Radar::getPos(){
	return currentPosition;
}

float  Radar::detectObj(){
  	float d = pSonar->getDistance();
  	if (d < SONAR_MAX_DIST){
  		return d;
  	} else {
  		return NO_OBJ_DETECTED;
  	}
}
