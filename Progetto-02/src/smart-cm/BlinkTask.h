#ifndef __BLINKTASK__
#define __BLINKTASK__

#include "Task.h"
#include "Led.h"

class BlinkTask: public Task {
private:
  int pin;
  int cicli;
  Led* ledd, * leda;
  enum { ON, OFF} led1state, led2state;
  enum { WAITING, BLINKING, ALARMING} state;

public:

  BlinkTask(Led* leda, Led* ledd);  
  void init(int period);  
  void tick();
};

#endif
