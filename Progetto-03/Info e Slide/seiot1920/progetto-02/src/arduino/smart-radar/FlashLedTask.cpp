#include "FlashLedTask.h"
#include "Arduino.h"
#include "Logger.h"

#define FLASH_TIME 20

FlashLedTask::FlashLedTask(Light* pLed){ 
  this->pLed = pLed;  
}
  
void FlashLedTask::init(){
  Task::init();
  setActive(true);
  state = INIT;
}
 

void FlashLedTask::tick(){
  switch (state){
    case INIT: {
      pLed->switchOn();
      ts0 = millis();
      state = FLASHING;
      break;
    }
    case FLASHING: {
      long ts = millis();
      if (ts - ts0 > FLASH_TIME){
        pLed->switchOff();
        setCompleted();
      }
      break;
    }
  }
}
