#include "ManualModeTask.h"
#include "Arduino.h"
#include "Logger.h"

#define MANUAL_DELTAROT 10
#define MANUAL_DELTATS 100

ManualModeTask::ManualModeTask(Radar* pRadar, UserConsole* pUserConsole, FlashLedTask* pFlashTask){
  this->pRadar = pRadar;
  this->pUserConsole = pUserConsole;
  this->pFlashTask = pFlashTask;
}
  
void ManualModeTask::init(int period){
  Task::init(period);
  state = INIT;
}

void ManualModeTask::setActive(bool active){
  Task::setActive(active);
  if (active){
    state = INIT;
  }
}
  
void ManualModeTask::tick(){
  switch (state){
    case INIT: {
      pUserConsole->reset();
      pUserConsole->notifyMode(USER_CONSOLE_MODE_MANUAL);
      pRadar->setPos(0);
      pUserConsole->notifyNewPos(pRadar->getPos()); 
      state = DETECTING;
      break;
    }
    case DETECTING: {
      float dist = pRadar->detectObj();
      if (dist >= 0){
        // Logger.log(String("MANUAL | obj det ") + dist);
        pUserConsole->notifyObjDetectedAt(pRadar->getPos(), dist);  
        pFlashTask->init();

      }
      state = CHECK_MOVING;
      break;
    }
    case CHECK_MOVING: {
      /*
      int newScanTime = pRadar->getScanTime();
      if (newScanTime != scanTime){
        scanTime = newScanTime;
        Logger.log(String("New scan time: ") + scanTime);
      }*/

      int cmd = pUserConsole->checkMoveCmd();
      if (cmd == USER_CONSOLE_ROTLEFT){
        // Logger.log("MANUAL | left ");
        startMovingTs = millis();
        pRadar->rotateLeft(MANUAL_DELTAROT);
        pUserConsole->notifyNewPos(pRadar->getPos()); 
        state = MOVING;
      } else if (cmd == USER_CONSOLE_ROTRIGHT){
        // Logger.log("MANUAL | right ");
        startMovingTs = millis();
        pRadar->rotateRight(MANUAL_DELTAROT);
        pUserConsole->notifyNewPos(pRadar->getPos()); 
        state = MOVING;
      } else {        
        state = DETECTING;
      }
      break;
    }
    case MOVING: {
      long ts = millis();
      if (ts - startMovingTs > MANUAL_DELTATS){
        state = DETECTING;
      }
      break;
    }
  }
}
