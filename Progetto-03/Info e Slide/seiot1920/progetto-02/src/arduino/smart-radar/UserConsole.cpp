#include "UserConsole.h"
#include "Arduino.h"
#include "MsgService.h"
#include "Logger.h"
#include "ButtonImpl.h"
#include "Led.h"
#include <avr/sleep.h>

void wakeUp(){}

UserConsole::UserConsole(int ldPin, int laPin, int potPin, int pirPin,
      int m1ButPin, int m2ButPin, int m3ButPin){
  pPot = new Potentiometer(potPin);
  pPir = new Pir(pirPin);
  pButtonSingle = new ButtonImpl(m1ButPin);
  pButtonManual = new ButtonImpl(m2ButPin);
  pButtonAuto = new ButtonImpl(m3ButPin);
  connected = false;
  cmdMode = USER_CONSOLE_NOCMD;
  cmdMove = USER_CONSOLE_NOCMD;
  pLedD = new Led(ldPin);
  pLedA = new Led(laPin);
  /* pirPin should be 2 or 3 */
  attachInterrupt(digitalPinToInterrupt(pirPin), wakeUp, RISING); 
}

void UserConsole::sleep(){
    reset();
    delay(100);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
    sleep_enable();
    sleep_mode();  
}

void UserConsole::reset(){
  pLedD->switchOff();
  pLedA->switchOff();
};

void UserConsole::notifySelfTest(){
  MsgService.sendMsg("sr:te");
};

void UserConsole::notifyReady(){
  MsgService.sendMsg("sr:ok");
  delay(10);
  MsgService.sendMsg(String("sr:pa|") + DNEAR + "|" + DFAR + "|" + SONAR_MAX_DIST);
};

void UserConsole::notifyAlarm(bool alarm){
  if (alarm){
    MsgService.sendMsg("sr:a1");  
  } else {
    MsgService.sendMsg("sr:a0");  
  }
};

void UserConsole::notifyMode(int value){
  MsgService.sendMsg(String("sr:mo|") + value);
};

void UserConsole::notifyNewPos(int degree){
  MsgService.sendMsg(String("sr:po|") + degree);
};

void UserConsole::notifyNewScan(){
  MsgService.sendMsg("sr:sc");
};

void UserConsole::notifyObjDetectedAt(int degree, float distance){
    MsgService.sendMsg(String("sr:de|") + degree + "|" + distance);
};

bool UserConsole::isConnected(){
  return connected;
}

void UserConsole::checkMsg(){
  Msg* msg = MsgService.receiveMsg();
  if (msg != NULL){
    String st = String(msg->getContent());
    // Logger.log(String("msg ") + st);    
    if (!connected){
      if (st == "ok"){
        connected = true;
      } 
    } else {
      if (st == "le"){
        cmdMove = USER_CONSOLE_ROTLEFT;
      } else if (st == "ri"){
        cmdMove = USER_CONSOLE_ROTRIGHT;
      }  else if (st == "m1"){
        cmdMode = USER_CONSOLE_MODE_SINGLE;
      }  else if (st == "m2"){
        cmdMode = USER_CONSOLE_MODE_MANUAL;
      }  else if (st == "m3"){
        cmdMode = USER_CONSOLE_MODE_AUTO;
      }     
    }
    delete msg;
  }
}

int UserConsole::checkMoveCmd(){
  int cmd1 = cmdMove;
  cmdMove = USER_CONSOLE_NOCMD;
  return cmd1;
}

int UserConsole::checkModeCmd(){
  int cmd1 = cmdMode;
  cmdMode = USER_CONSOLE_NOCMD;
  return cmd1;
}

int UserConsole::checkBoardModeCmd(){
  bool singleMode = pButtonSingle->isPressed();
  bool autoMode = pButtonAuto->isPressed();
  bool manualMode = pButtonManual->isPressed();
  if (singleMode){
    return USER_CONSOLE_MODE_SINGLE;
  } else if (manualMode){
    return USER_CONSOLE_MODE_MANUAL;
  } else if (autoMode){
    return USER_CONSOLE_MODE_AUTO;
  } else {
    return USER_CONSOLE_NOCMD;
  }
}

void UserConsole::calibrate(){
  // pPir->calibrate();
  pLedD->switchOn();
  delay(500);
  pLedA->switchOn();
  delay(500);
  pLedD->switchOff();
  pLedA->switchOff();
}

int UserConsole::getScanTime(){
  float value = pPot->getValue();
  return SCAN_TIME_MIN + (int) ((SCAN_TIME_MAX - SCAN_TIME_MIN) * value);
}

bool UserConsole::detectedPresence(){
  return pPir->isDetected();
}

Light* UserConsole::getLedD(){
  return pLedD;
}

Light* UserConsole::getLedA(){
  return pLedA;
}
