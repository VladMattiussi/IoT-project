#ifndef __AUTOTASK__
#define __AUTOTASK__

#include "Task.h"
#include "arduino.h"
#include "Sonar.h"
#include "Pot.h"
#include "Led.h"
#include "servo_motor_impl.h"

class AutoTask: public Task {
private:
  ServoMotor* pServo;
  Sonar* pProx;
  Potentiometer* pPot;
  int angolo;
  float sliceTime;
  unsigned long lastExecTime;
  enum {WAITDELAY, SCANNING, ALARM, TRACKING} state;
  void scan();
  void moveAndScan();
  

public:

  AutoTask(Sonar* pProx, Potentiometer* pPot, ServoMotor* pMotor);  
  void init(int period);  
  void tick();
};

#endif
