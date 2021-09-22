#include "BlinkTask.h"
#include "arduino.h"
#include "ActiveTasks.h"

BlinkTask::BlinkTask(Led* leda, Led* ledd){
  this->leda = leda; 
  this->ledd = ledd;
  this->led1state = OFF;
  this->led2state = OFF;
  this->cicli=0;
  this->state=WAITING;
}
  
void BlinkTask::init(int period){
  Task::init(period);
}
  
void BlinkTask::tick(){
  switch(state){
    case WAITING:
      if(ActiveTasks::getInstance()->getBlinkState()){
        this->cicli=2;
        ActiveTasks::getInstance()->setBlinkState(false);
        this->state=BLINKING;
      }
      else if(ActiveTasks::getInstance()->getAlarmState()){
        this->state=ALARMING;
      }
      break;
    case BLINKING:
      switch (led1state){
      case OFF:
        ledd->switchOn();
        led1state = ON;
        break;
      case ON:
        ledd->switchOff();
        led1state = OFF;
        break;
    }
    cicli--;
    if(cicli<=0){
      this->state=WAITING;
    }
    break;
    case ALARMING:
      switch (led2state){
        case OFF:
          leda->switchOn();
          led2state = ON;
          break;
        case ON:
          leda->switchOff();
          led2state = OFF;
          if(!ActiveTasks::getInstance()->getAlarmState()){
            state=WAITING; 
          }
          break;
      }
      
  }
}
