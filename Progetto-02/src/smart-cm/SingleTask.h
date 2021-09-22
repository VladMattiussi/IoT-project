#ifndef __SINGLETASK__
#define __SINGLETASK__

#include "Task.h"
#include "arduino.h"
#include "Sonar.h"
#include "Pot.h"
#include "Led.h"
#include "servo_motor_impl.h"
#include "Pir.h"

class SingleTask: public Task {
private:
  ServoMotor* pServo;
  Sonar* pProx;
  Potentiometer* pPot;
  Pir* pPir;
  int angolo;
  float sliceTime;
  unsigned long lastExecTime;
  enum { WAITDELAY, WAITING, SCANNING} state;
  void scan();
  

public:

  SingleTask(Sonar* pProx, Potentiometer* pPot, ServoMotor* pMotor, Pir* pPir);  
  void init(int period);  
  void tick();
};

#endif
