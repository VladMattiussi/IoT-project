#include <stdlib.h>
#include <Arduino.h>
#include "InputTask.h"
#include "ActiveTasks.h"
#include "Button.h"
#include "Config.h"
#include "MsgService.h"

InputTask::InputTask(Button* b1, Button* b2, Button* b3){

    this->buttonSingle=b1;
    this->buttonManual=b2;
    this->buttonAuto=b3;
}
  
void InputTask::init(int period){
    
    Task::init(period);    
}
  
void InputTask::tick(){
  
    Msg* msg = MsgService.receiveMsg();    
    
    if(buttonSingle->isPressed() == true || msg->getContent() == "single"){
      Serial.println("SingleMode");
      ActiveTasks::getInstance()->switchMode(SINGLE_TASK);
      ActiveTasks::getInstance()->setResetState(true);
    }
    if(buttonManual->isPressed() == true || msg->getContent() == "manual"){
      Serial.println("ManualMode");
      ActiveTasks::getInstance()->switchMode(MANUAL_TASK);
      ActiveTasks::getInstance()->setResetState(true);
    }
    if(buttonAuto->isPressed() == true  || msg->getContent() == "auto"){
      Serial.println("AutoMode");
      ActiveTasks::getInstance()->switchMode(AUTO_TASK);
      ActiveTasks::getInstance()->setResetState(true);
    }
        
    }
