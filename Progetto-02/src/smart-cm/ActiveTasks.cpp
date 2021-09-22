#include "ActiveTasks.h"
#include "Task.h"
ActiveTasks* ActiveTasks::at = NULL; 
ActiveTasks* ActiveTasks::getInstance(){
  if (!at) {
    at = new ActiveTasks();
  }
    return at;
}

bool ActiveTasks::isActive(int tid){
    return activeTasks[tid]; 
}

void ActiveTasks::setResetState(bool option){
    this->resetState = option;
}

bool ActiveTasks::getResetState(){
    return resetState; 
}

void ActiveTasks::setAlarmState(bool option){
    this->alarmState = option;
}

bool ActiveTasks::getAlarmState(){
    return alarmState; 
}

void ActiveTasks::setBlinkState(bool option){
    this->blinkState = option;
}

bool ActiveTasks::getBlinkState(){
    return this->blinkState;
}

void ActiveTasks::manageTasks(int tid, bool option){
  activeTasks[tid]=option;
}

void ActiveTasks::switchMode(int tid){
  if(tid>=0 && tid<=N_OF_MODES-1){
    manageTasks(tid, true);
    manageTasks((tid+1)%3, false);
    manageTasks((tid+2)%3, false);

    setBlinkState(false);
    setAlarmState(false);

    Serial.println("switchMode called, ActiveTasks:");
  }
  else {
    Serial.println("Non valid tid (0-1-2)");
  }
  for(int i=0; i<5; i++){
    Serial.println(activeTasks[i]);
  }
  
}
  
