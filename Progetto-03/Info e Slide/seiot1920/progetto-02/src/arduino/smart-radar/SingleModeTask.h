#ifndef __SINGLEMODETASK__
#define __SINGLEMODETASK__

#include "Task.h"
#include "Radar.h"
#include "UserConsole.h"
#include "FlashLedTask.h"

class SingleModeTask: public Task {

public:

  SingleModeTask(Radar* pRadar, UserConsole* pUserConsole, FlashLedTask* pFlashLedTask);  
  void init(int period);  
  void setActive(bool active);
  void tick();

private:

  enum { INIT, WAIT_FOR_PRESENCE, START, UPDATING_POS, DETECTING, MOVING } state;
 
  int sectorIndex;
  float deltaRot;
  int timeToRotASector;
  long  startTimeMoving;
  long  startTimeInSector;
  Radar* pRadar;
  UserConsole* pUserConsole;
  FlashLedTask* pFlashTask;
  
};

#endif
