#include "Arduino.h"
#include "config.h"
#include "game_core.h"
#include "user_input.h"

int ledPin[] = {LED01_PIN, LED02_PIN, LED03_PIN};

void initLedBoard(){   
  for (int i = 0; i < 3; i++){
    pinMode(ledPin[i], OUTPUT);     
  }
  pinMode(LEDBAG_PIN,OUTPUT);  
  pinMode(LEDERROR_PIN,OUTPUT);  
}

void resetLedBoard(){   
  for (int i = 0; i < 3; i++){
    digitalWrite(ledPin[i], LOW);     
  }
  digitalWrite(LEDERROR_PIN, LOW);
  digitalWrite(LEDBAG_PIN, LOW);
}

void switchObjLed(int pos, int state){
  digitalWrite(ledPin[pos], state);
}

void switchBagLed(int state){
  digitalWrite(LEDBAG_PIN, state);
}

void pulseBagLed(){
  for (int i = 0; i < 255; i+= 25){
    analogWrite(LEDBAG_PIN, i);
    delay(7);
  }
  for (int i = 225; i >= 0; i-= 25){
    analogWrite(LEDBAG_PIN, i);
    delay(7);
  }
}

void switchErrorLed(int state){
  digitalWrite(LEDERROR_PIN, state);
}
