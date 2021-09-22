#include "Scheduler.h"
#include "Config.h"
#include "MsgService.h"
#include "Pot.h"
#include "Sonar.h"
#include "Led.h"
#include "Pir.h"
#include "Task.h"

#include "servo_motor_impl.h"
#include "servo_motor.h"
#include "AutoTask.h"
#include "ManualTask.h"
#include "SingleTask.h"
#include "InputTask.h"
#include "BlinkTask.h"
#include "ActiveTasks.h"

Scheduler sched;
void wakeUp() {}

void setup(){

  sched.init(BASE_PERIOD);
  MsgService.init();

  Sonar* pSonar = new Sonar(SONAR_ECHO_PIN, SONAR_TRIG_PIN);
  Potentiometer* pPot = new Potentiometer(POTENZIOMETRO_PIN);
  Led* leda = new Led(LED_PIN1);
  Led* ledd = new Led(LED_PIN2);
  ServoMotor* pServo = new ServoMotorImpl(SERVO_PIN);
  Pir* pPir = new Pir(PIR_PIN);
  attachInterrupt(digitalPinToInterrupt(2), wakeUp, RISING); 
  Button* b1 = new Button(BUTTON_PIN1);
  Button* b2 = new Button(BUTTON_PIN2);
  Button* b3 = new Button(BUTTON_PIN3);
  

  Task* single = new SingleTask(pSonar,pPot, pServo,pPir);
  single->init(BASE_PERIOD);
  sched.addTask(single);
  
  Task* manual = new ManualTask(pSonar,pPot, pServo); 
  manual->init(BASE_PERIOD); //Da abbassare, usa 1000 per test senza gui
  sched.addTask(manual);
  
  Task* automatic = new AutoTask(pSonar,pPot, pServo);
  automatic->init(BASE_PERIOD);
  sched.addTask(automatic);
  
  Task* input = new InputTask(b1,b2,b3);
  input->init(BASE_PERIOD);
  sched.addTask(input);

  Task* blink = new BlinkTask(leda, ledd);
  blink->init(200);
  sched.addTask(blink);

  pServo->on();
  ActiveTasks::getInstance()->manageTasks(INPUT_TASK, true);
  ActiveTasks::getInstance()->manageTasks(BLINK_TASK, true);
  ActiveTasks::getInstance()->switchMode(MANUAL_TASK);
}

void loop(){
  sched.schedule();
}
