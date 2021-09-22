#ifndef __MANUALTASK__
#define __MANUALTASK__

#include "Task.h"
#include "arduino.h"
#include "Sonar.h"
#include "Pot.h"
#include "servo_motor_impl.h"

class ManualTask: public Task {

ServoMotor* pServo;
Sonar* pProx;
Potentiometer* pPot;
String message;
enum {WAITING, SCANNING} state;
  

public:

  ManualTask(Sonar* pProx, Potentiometer* pPot, ServoMotor* pMotor);  
  void scan();
  void init(int period);  
  void tick();
};
#endif
