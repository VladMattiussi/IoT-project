#ifndef __FLASHLEDTASK__
#define __FLASHLEDTASK__

#include "Task.h"
#include "Light.h"

class FlashLedTask: public Task {
  
public:
  FlashLedTask(Light* pLed);  

  void init();
  void tick();

private:

  long ts0;	
  Light* pLed;
  enum { INIT, FLASHING } state;

};

#endif
