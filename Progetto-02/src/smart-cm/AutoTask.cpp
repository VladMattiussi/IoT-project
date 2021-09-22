#include "AutoTask.h"
#include "MsgService.h"
#include <stdlib.h>
#include "Config.h"
#include <Arduino.h>
#include "ActiveTasks.h"

AutoTask::AutoTask(Sonar* pProx, Potentiometer* pPot, ServoMotor* pServo){
    this->pPot=pPot;
    this->pProx=pProx;
    this->pServo=pServo;
    this->angolo=0;
    this->state = SCANNING;
}

void AutoTask::scan(){
        float dist = pProx->getDistance();
        if(dist> DNEAR && dist< DFAR){
          Serial.println("Oggetto compreso tra Dnear e Dfar");
          this->state = ALARM;      
        } 
        else if(dist<DNEAR){
            Serial.println("Oggetto < Dnear");
            this->state = TRACKING;
            
        }
        else{
          Serial.println("Oggetto > Dfar");
          ActiveTasks::getInstance()->setAlarmState(false);
          this->state = WAITDELAY;
        }
        
}

void AutoTask::moveAndScan(){
  this->angolo+=ARCO;
  if(this->angolo>180){
    this->angolo=0;
  }
  pServo->setPosition(angolo);
  this->scan();
  this->lastExecTime=millis();
}
void AutoTask::init(int period){
    Task::init(period);    
}
  
void AutoTask::tick(){
  if(ActiveTasks::getInstance()->getResetState()){
    float potValue = map(pPot->getValue(), 0, 1023, 0, 100);
    sliceTime= ((TMIN+((TMAX-TMIN) * potValue/100))/16)*1000;  // NB valore minimo del ciclo è 2s, massimo 10s, Ogni spicchio va fatto in un sedicesimo del tempo di ciclo
    this->angolo=0;
    this->state=SCANNING;
    this->lastExecTime=millis();
    ActiveTasks::getInstance()->setResetState(false);
  }
  switch(state){
    case WAITDELAY:
        if(millis()-lastExecTime > sliceTime-BASE_PERIOD){
          this->state=SCANNING;
        }
        break;
    case TRACKING:
        ActiveTasks::getInstance()->setAlarmState(true);
        this->scan();
        break;
    case ALARM:
        ActiveTasks::getInstance()->setAlarmState(true);
        this->state = WAITDELAY;
        break;
    case SCANNING:
        this->moveAndScan();
        break;
    }
}
