#ifndef __USER_CONSOLE__
#define __USER_CONSOLE__

#include "config.h"
#include "Pot.h"
#include "Pir.h"
#include "Button.h"
#include "light.h"

#define USER_CONSOLE_NOCMD     0
#define USER_CONSOLE_ROTLEFT   1
#define USER_CONSOLE_ROTRIGHT  2

#define USER_CONSOLE_MODE_SINGLE 1
#define USER_CONSOLE_MODE_MANUAL 2
#define USER_CONSOLE_MODE_AUTO 	3

class UserConsole {

public:
  UserConsole(int ldPin, int laPin, int potPin, int pirPin, int m1ButPin, int m2ButPin, int m3ButPin);

  void notifyReady();
  void notifyMode(int mode);
  void notifySelfTest();
  void notifyAlarm(bool alarm);
  void notifyNewScan();
  void notifyNewPos(int degree);
  void notifyObjDetectedAt(int degree, float distance);
  int  checkMoveCmd();
  int  checkModeCmd();
  int  checkBoardModeCmd();
  bool isConnected();  
  void checkMsg();
  void sleep();
  void reset();

  void calibrate();
  int  getScanTime();
  bool detectedPresence();
  Light* getLedD();
  Light* getLedA();


private:
  bool connected;
  int cmdMove;
  int cmdMode;
  Light* pLedD;
  Light* pLedA;
  Potentiometer* pPot;
  Pir* pPir;
  Button* pButtonSingle; 
  Button* pButtonAuto; 
  Button* pButtonManual; 

};

#endif
