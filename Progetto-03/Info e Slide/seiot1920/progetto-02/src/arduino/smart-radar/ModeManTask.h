#ifndef __MODEMANTASK__
#define __MODEMANTASK__

#include "Task.h"
#include "UserConsole.h"
#include "ManualModeTask.h"
#include "SingleModeTask.h"
#include "AutoModeTask.h"

class ModeManTask: public Task {

public:

  ModeManTask(ManualModeTask* pManMode, AutoModeTask* pAutoMode, SingleModeTask* pSingleMode, UserConsole* pUserConsole);  
  void init(int period);  
  void tick();

private:

  enum { WAITING_FOR_CONNECTION, CONNECTED } state;
 
  int currentMode;

  ManualModeTask* pManualMode;
  AutoModeTask* pAutoMode;
  SingleModeTask* pSingleMode;
  UserConsole* pUserConsole;
  Task* pCurrentModeTask;

  
};

#endif
