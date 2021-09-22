#include "SingleModeTask.h"
#include "Arduino.h"
#include "Logger.h"
#include "config.h"


SingleModeTask::SingleModeTask(Radar* pRadar, UserConsole* pUserConsole, FlashLedTask* pFlashTask){
  this->pRadar = pRadar;
  this->pUserConsole = pUserConsole;
  this->pFlashTask = pFlashTask;
  timeToRotASector = 20;
};
  
void SingleModeTask::init(int period){
  Task::init(period);
  state = INIT;
};
  
void SingleModeTask::setActive(bool active){
  Task::setActive(active);
  if (active){
    state = INIT;
  }
  // Logger.log("SINGLE | switched to " + active);
}

void SingleModeTask::tick(){
  switch (state){
    case INIT: {
      // Logger.log(String("SINGLE | ready ") + pRadar->getScanTime());
      pUserConsole->notifyMode(USER_CONSOLE_MODE_SINGLE);
      pUserConsole->reset();
      state = WAIT_FOR_PRESENCE;
    }
    case WAIT_FOR_PRESENCE: {
      pUserConsole->sleep();
      if (pUserConsole->detectedPresence()){
        state = START;
      }
      break;
    }
    case START: {
      deltaRot = 180 / NUM_SECTORS;
      float startPos = deltaRot / 2;
      sectorIndex = 1;
      pUserConsole->notifyNewScan(); 
      pRadar->setPos(startPos);
      startTimeMoving = millis();
      state = MOVING;
      break;
    }
    case UPDATING_POS: {
      sectorIndex++;
      if (sectorIndex <= NUM_SECTORS) {
        // Logger.log(String("SINGLE | updating pos.."));
        startTimeMoving = millis();

        pRadar->rotateRight(deltaRot);
        state = MOVING;
      } else {
        // Logger.log(String("SINGLE | done"));
        pRadar->setPos(0);
        pUserConsole->notifyNewPos(pRadar->getPos()); 
        state = WAIT_FOR_PRESENCE;
      }
      break;
    }
    case MOVING: {
      long ts = millis();
      if (ts - startTimeMoving > timeToRotASector){
          pUserConsole->notifyNewPos(pRadar->getPos()); 
          startTimeInSector = millis();
          state = DETECTING;
      }
      break;
    }
    case DETECTING: {
      float dist = pRadar->detectObj();
      if (dist >= 0){
        pUserConsole->notifyObjDetectedAt(pRadar->getPos(), dist); 
        pFlashTask->init(); 
      } 

      long ts = millis();
      long dt = pUserConsole->getScanTime() / NUM_SECTORS;
      if (ts - startTimeInSector > dt){
        state = UPDATING_POS;  
      }
      break;
    }
  }
};
