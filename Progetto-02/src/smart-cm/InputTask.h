#ifndef __INPUTTASK__
#define __INPUTTASK__

#include "Task.h"
#include "arduino.h"
#include "Button.h"

class InputTask: public Task {
private: 
  Button* buttonSingle;
  Button* buttonManual;
  Button* buttonAuto;
public:

  InputTask(Button* b1, Button* b2, Button* b3);
    
  void init(int period);  
  void tick();
};

#endif
