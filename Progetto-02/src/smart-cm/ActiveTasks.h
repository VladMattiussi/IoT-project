#ifndef __ACTIVETASKS__
#define __ACTIVETASKS__
#define MAXTASKS 50
#include "Arduino.h"

class ActiveTasks {
public:
  static ActiveTasks* getInstance();
  bool isActive(int tid);
  void setBlinkState(bool option);
  bool  getBlinkState();
  void setResetState(bool option);
  bool getResetState();
  void setAlarmState(bool option);
  bool getAlarmState();
  void manageTasks(int tid, bool option);
  void switchMode(int tid);
  
private:
  static ActiveTasks* at;
  bool resetState=false;
  bool alarmState=false;
  bool blinkState = false;
  ActiveTasks(){};
  void scan();
  
  
  bool activeTasks[MAXTASKS]={0};
};

#endif
