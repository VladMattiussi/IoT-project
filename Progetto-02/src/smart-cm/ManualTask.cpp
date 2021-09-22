#include "ManualTask.h"
#include "ActiveTasks.h"
#include "Led.h"
#include "MsgService.h"
#include <stdlib.h>
#include "String.h"
#include "Config.h"

ManualTask::ManualTask(Sonar* pProx, Potentiometer* pPot, ServoMotor* pServo){

    this->pPot=pPot;
    this->pProx=pProx;
    this->pServo=pServo;
    this->state=WAITING;
    this->message="";
}

void ManualTask::scan(){
        float dist = pProx->getDistance();
        if(dist<2){
          Serial.println("Oggetto a distanza: ");
          Serial.println(dist);
        }
}
  
void ManualTask::init(int period){
    
    Task::init(period);    
}
  
void ManualTask::tick(){
  if(ActiveTasks::getInstance()->getResetState()){
    this->state=WAITING;
    ActiveTasks::getInstance()->setResetState(false);
  }
  switch(state){
    case WAITING:
        
        if (MsgService.isMsgAvailable()) {
          Msg* msg = MsgService.receiveMsg();
          this->message= msg->getContent();
          int m = msg->getContent().toInt();
          this->pServo->setPosition(m);
          float f = this->pProx->getDistance();
          Serial.println("La distanza è ");
          Serial.println(f);
          delete msg;
        }
        break;
    case SCANNING:
        //execute input
        //int e = this->message.toInt(); 
        
        //this->scan();
        break;
    }
}
/*
    // Controllo se devo muovere il servo
    

    int m = 0;
    //m = atoi(msg->getContent().c_str);
    //m = atoi(msg->getContent());  
    if (m > 0 && m < 180){

       // Ruoto il servomotore
       pServo->setPosition(m);
       
       // Attivo il sonar
       float dist = pProx->getDistance();
       if(dist>0){
           MsgService.sendMsg("La distanza dell'oggetto è: ");
       } else {
           MsgService.sendMsg("Nessun oggetto rilevato");
       }
    }

    // Dealloco il messaggio
    delete msg;

  }

    // PROVA SENZA GUI PER VEDERE SE FUNZIONA
    int gradi = 87;
    //pServo->on();
   // pServo->setPosition(gradi);
    float dist = pProx->getDistance();
    Serial.println(dist);
    // FINE PROVA
    */
