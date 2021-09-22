/*
 * SMART RADAR - Progetto 02 - SEIOT a.a. 2019-2020
 * 
 * Esempio di soluzione.
 * 
 */
#include "config.h"
#include "Scheduler.h"
#include "Logger.h"
#include "MsgService.h"
#include "Radar.h"
#include "UserConsole.h"
#include "ModeManTask.h"

Scheduler sched;

void setup(){

  sched.init(20);
  MsgService.init();

  UserConsole* pUserConsole = new UserConsole(LD_PIN, LA_PIN, POT_PIN, PIR_PIN, BUTTON_TM1_PIN, BUTTON_TM2_PIN, BUTTON_TM3_PIN);
  pUserConsole->calibrate();
  
  Radar* pRadar = new Radar(RADAR_ECHO_PIN, RADAR_TRIG_PIN, RADAR_SERVO_PIN);
    
  Task* pFlashTask = new FlashLedTask(pUserConsole->getLedD());
  pFlashTask->setActive(false);

  Task* pBlinkingTask = new BlinkingTask(pUserConsole->getLedA());
  pBlinkingTask->init(40);
  pBlinkingTask->setActive(false);
      
  Task* pSingleModeTask = new SingleModeTask(pRadar, pUserConsole, pFlashTask);
  pSingleModeTask->init(20);
  pSingleModeTask->setActive(false);

  Task* pManualModeTask = new ManualModeTask(pRadar, pUserConsole, pFlashTask);
  pManualModeTask->init(100);
  pManualModeTask->setActive(false);

  Task* pAutoModeTask = new AutoModeTask(pRadar, pUserConsole, pFlashTask, pBlinkingTask);
  pAutoModeTask->init(20);
  pAutoModeTask->setActive(false);

  Task* pModeManTask = new ModeManTask(pManualModeTask, pAutoModeTask, pSingleModeTask, pUserConsole);
  pModeManTask->init(100);
  
  sched.addTask(pModeManTask);
  sched.addTask(pSingleModeTask);
  sched.addTask(pManualModeTask);
  sched.addTask(pAutoModeTask);
  sched.addTask(pFlashTask); 
  sched.addTask(pBlinkingTask); 
}

void loop(){
  sched.schedule();
}
