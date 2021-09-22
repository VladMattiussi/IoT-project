#include "AutoModeTask.h"
#include "Arduino.h"
#include "Logger.h"
#include "config.h"

AutoModeTask::AutoModeTask(Radar* pRadar, UserConsole* pUserConsole, 
          FlashLedTask* pFlashTask, BlinkingTask* pBlinkTask){
  this->pRadar = pRadar;
  this->pUserConsole = pUserConsole;
  this->pFlashTask = pFlashTask;
  this->pBlinkTask = pBlinkTask;
  timeToRotASector = 20;
};
  
void AutoModeTask::init(int period){
  Task::init(period);
  state = INIT;
  deltaRot = 180 / NUM_SECTORS;  
}
  
void AutoModeTask::setActive(bool active){
  Task::setActive(active);
  if (active){
    state = INIT;
  } else {
    pBlinkTask->setActive(false);  
  }
}

void AutoModeTask::tick(){
  switch (state){
    case INIT: {
      pUserConsole->reset();
      pUserConsole->notifyMode(USER_CONSOLE_MODE_AUTO);
      ongoingAlarm = false;
      state = START;
      break;
    }
    case START: {
      sectorIndex = 1;
      newAlarm = false;
      pUserConsole->notifyNewScan(); 
      pRadar->setPos(deltaRot / 2);
      startTimeMoving = millis();
      state = MOVING;
      break;
    }
    case UPDATING_POS: {
      sectorIndex++;
      if (sectorIndex <= NUM_SECTORS) {
        startTimeMoving = millis();
        pRadar->rotateRight(deltaRot);
        state = MOVING;
      } else {
        if (newAlarm){
          ongoingAlarm = true;
        } else {
          if (ongoingAlarm){
            pBlinkTask->setActive(false);  
          }
          ongoingAlarm = false;
        }
        state = START;
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
        if (dist <= DFAR){
           if (dist >= DNEAR){
                if (!newAlarm && !ongoingAlarm){
                  pBlinkTask->setActive(true); 
                  newAlarm = true; 
                }
           } else {
              // Logger.log("SEVERE ALARM");
              pUserConsole->notifyAlarm(true);
              state = TRACKING;
              break;
           }
        }
      } 

      long ts = millis();
      long dt = pUserConsole->getScanTime() / NUM_SECTORS;
      if (ts - startTimeInSector > dt){
        state = UPDATING_POS;  
      }
      break;
    }
    case TRACKING: {
      float dist = pRadar->detectObj();
      if (dist >= 0){
        pUserConsole->notifyObjDetectedAt(pRadar->getPos(), dist); 
        if (dist >= DNEAR){
          pUserConsole->notifyAlarm(false);
          state = UPDATING_POS;
        }
      } else {
        pUserConsole->notifyAlarm(false);
        state = UPDATING_POS;
      }
      break;
    }
  }
}
