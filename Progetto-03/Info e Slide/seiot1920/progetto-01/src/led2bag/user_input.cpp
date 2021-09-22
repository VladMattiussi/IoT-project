#include "Arduino.h"
#include "config.h"

const int difficultyStep = 1024 / NLEVELS;

/* flag used to keep track if button TS is pressed */
bool buttonTSPressedFlag = false;

/* for debouncing */
long lastButtonTSPressedTimeStamp = 0;

/* flag used to keep track if button TD is pressed */
bool buttonTDPressedFlag = false;

/* for debouncing */
long lastButtonTDPressedTimeStamp = 0;

/* interrupt handler for button TS */
void buttonTSPressedHandler(){
  long ts = millis();
  if (ts - lastButtonTSPressedTimeStamp > BOUNCING_TIME_TS){
    buttonTSPressedFlag = true;      
    lastButtonTSPressedTimeStamp = ts;
  }
}

/* interrupt handler for button TD */
void buttonTDPressedHandler(){
  long ts = millis();
  if (ts - lastButtonTDPressedTimeStamp > BOUNCING_TIME_TD){
    buttonTDPressedFlag = true;      
    lastButtonTDPressedTimeStamp = ts;
  }
}

void initPlayerInput(){
  pinMode(TS_PIN, INPUT);     
  pinMode(TD_PIN, INPUT);     
  attachInterrupt(digitalPinToInterrupt(TS_PIN), buttonTSPressedHandler, RISING); 
  attachInterrupt(digitalPinToInterrupt(TD_PIN), buttonTDPressedHandler, RISING); 
}

void resetPlayerInput(){
  buttonTSPressedFlag = false;
  buttonTDPressedFlag = false;
  lastButtonTSPressedTimeStamp = 0;
  lastButtonTDPressedTimeStamp = 0;
}

int getDifficultyLevel(){
  int value = analogRead(POT_PIN);
  return value / difficultyStep + 1;
}

bool buttonTSpressed(){
  noInterrupts();
  bool value = buttonTSPressedFlag;  
  buttonTSPressedFlag = false;
  interrupts();
  return value; 
}

bool buttonTDpressed(){
  noInterrupts();
  bool value = buttonTDPressedFlag;  
  buttonTDPressedFlag = false;
  interrupts();
  return value; 
}
