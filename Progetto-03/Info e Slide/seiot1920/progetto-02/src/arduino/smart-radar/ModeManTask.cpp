#include "ModeManTask.h"
#include "Arduino.h"
#include "Logger.h"
#include "config.h"

ModeManTask::ModeManTask(ManualModeTask* pManMode, AutoModeTask* pAutoMode, SingleModeTask* pSingleMode, UserConsole* pUserConsole){
  this->pUserConsole = pUserConsole;
  this->pManualMode = pManMode;
  this->pSingleMode = pSingleMode;
  this->pAutoMode = pAutoMode;
};
  
void ModeManTask::init(int period){
  Task::init(period);
  state = WAITING_FOR_CONNECTION;
};
  
void ModeManTask::tick(){
  pUserConsole->checkMsg();
  switch (state){
    case WAITING_FOR_CONNECTION: {
      if (pUserConsole->isConnected()){
         pUserConsole->notifyReady();
         pManualMode->setActive(true);
         pCurrentModeTask = pManualMode;

         currentMode = USER_CONSOLE_MODE_MANUAL;
         state = CONNECTED;
      }
      break;
    }
    case CONNECTED: {   
      int modeCmd = pUserConsole->checkModeCmd(); 
      int modeCmdBoard = pUserConsole->checkBoardModeCmd();

      if (modeCmd == USER_CONSOLE_MODE_SINGLE || modeCmdBoard == USER_CONSOLE_MODE_SINGLE){
        if (currentMode != modeCmd){
          currentMode = USER_CONSOLE_MODE_SINGLE;  
          pCurrentModeTask->setActive(false);
          pCurrentModeTask = pSingleMode;    
          pCurrentModeTask->setActive(true);
        }  
      } else if (modeCmd == USER_CONSOLE_MODE_MANUAL || modeCmdBoard == USER_CONSOLE_MODE_MANUAL){
        if (currentMode != modeCmd){
          currentMode = USER_CONSOLE_MODE_MANUAL;     
          pCurrentModeTask->setActive(false);
          pCurrentModeTask = pManualMode;    
          pCurrentModeTask->setActive(true);
        }  
      } else if (modeCmd == USER_CONSOLE_MODE_AUTO || modeCmdBoard == USER_CONSOLE_MODE_AUTO){
        if (currentMode != modeCmd){
          currentMode = USER_CONSOLE_MODE_AUTO;      
          pCurrentModeTask->setActive(false);
          pCurrentModeTask = pAutoMode;    
          pCurrentModeTask->setActive(true);
        }  
      }
      break;
    }
  }
};
