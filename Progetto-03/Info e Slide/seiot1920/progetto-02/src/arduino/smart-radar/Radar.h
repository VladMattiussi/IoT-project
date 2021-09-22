#ifndef __RADAR__
#define __RADAR__

#include "sonar.h"
#include "servo_motor.h"
#include "config.h"

#define NO_OBJ_DETECTED -1


class Radar {
 
public: 
  Radar(int echoPin, int trigPin, int servoPin);
  void calibrate();
  void selfTest();
  
  void rotateLeft(float angle);
  void rotateRight(float angle);
  void setPos(float angle);
  float  getPos();
  float  detectObj();


private:
  float currentPosition;
  Sonar* pSonar;
  ServoMotor* pServo; 
};

#endif
