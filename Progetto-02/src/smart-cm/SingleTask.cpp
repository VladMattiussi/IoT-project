#include "SingleTask.h"
#include "ActiveTasks.h"
#include "MsgService.h"
#include <stdlib.h>
#include "Config.h"
#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/power.h>
SingleTask::SingleTask(Sonar* pProx, Potentiometer* pPot, ServoMotor* pServo, Pir* pPir){
    this->pPot=pPot;
    this->pProx=pProx;
    this->pServo=pServo;
    this->pPir=pPir;
    this->angolo=0;
    this->state= WAITING;
}
void sleep(void)
{
 set_sleep_mode(SLEEP_MODE_PWR_DOWN);
 sleep_enable();
 sleep_mode(); 
 /* back */
 sleep_disable();
}

void SingleTask::scan(){
        float dist = pProx->getDistance();
        if(dist<DFAR){
          ActiveTasks::getInstance()->setBlinkState(true);
          MsgService.sendMsg("OggettO rilevato! Distanza:");
          Serial.println(dist);
        } 
        else{
          MsgService.sendMsg("Nessun oggetto rilevato");
        }
}
  
void SingleTask::init(int period){
    Task::init(period);    
}
  
void SingleTask::tick(){
  if(ActiveTasks::getInstance()->getResetState()){
    this->state=WAITING;
    this->angolo=0;
    this->lastExecTime=millis();
    ActiveTasks::getInstance()->setResetState(false);
  }
    switch(state){
      case WAITDELAY:
        if(millis()-lastExecTime > sliceTime-BASE_PERIOD){
          this->lastExecTime=millis();
          this->state=SCANNING;
        }
        break;
      case WAITING:
        Serial.println("Waiting for pir (going in sleep mode)");
        Serial.flush();
        sleep();
        Serial.println(" pir movement detected, exiting sleep mode!");

        if(pPir->isDetected() == true){
          float potValue = map(pPot->getValue(), 0, 1023, 0, 100);
          sliceTime= ((TMIN+((TMAX-TMIN) * potValue/100))/16)*1000;
          this->state=SCANNING;
        }
        break;
      case SCANNING:
        pServo->setPosition(angolo);
        this->scan();
        this->angolo+=ARCO;
        if(this->angolo>180){
            this->angolo=0;
            this->state=WAITING;
            break;
        } 
        this->state=WAITDELAY;
        break;
    }         
}
