#ifndef __MANUALMODETASK__
#define __MANUALMODETASK__

#include "Task.h"
#include "Radar.h"
#include "UserConsole.h"
#include "FlashLedTask.h"

class ManualModeTask: public Task {
  
public:

  ManualModeTask(Radar* pRadar, UserConsole* pUserConsole, FlashLedTask* pFlashTask);  
  void init(int period);  
  void setActive(bool active);
  void tick();

private:
  
  Radar* pRadar;
  UserConsole* pUserConsole;
  FlashLedTask* pFlashTask;
  enum { INIT, DETECTING, CHECK_MOVING, MOVING } state;
  int scanTime;
  long startMovingTs;
};

#endif
