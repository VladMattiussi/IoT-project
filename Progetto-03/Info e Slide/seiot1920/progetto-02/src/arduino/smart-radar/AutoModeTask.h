#ifndef __AUTOMODETASK__
#define __AUTOMODETASK__

#include "Task.h"
#include "Radar.h"
#include "UserConsole.h"
#include "FlashLedTask.h"
#include "BlinkingTask.h"

class AutoModeTask: public Task {

public:

  AutoModeTask(Radar* pRadar, UserConsole* pUserConsole, FlashLedTask* pFlashLedTask, BlinkingTask* pBlinkTask);  
  void init(int period);  
  void setActive(bool active);  
  void tick();

private:

 enum { INIT, START, UPDATING_POS, DETECTING, MOVING, TRACKING } state;
 
  int sectorIndex;
  float deltaRot;
  int timeToRotASector;
  long  startTimeMoving;
  long  startTimeInSector;
  Radar* pRadar;
  UserConsole* pUserConsole;
  FlashLedTask* pFlashTask;
  BlinkingTask* pBlinkTask;
  bool newAlarm;
  bool ongoingAlarm;

};

#endif
