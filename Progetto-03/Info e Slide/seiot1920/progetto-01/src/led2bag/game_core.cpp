#include "Arduino.h"
#include "config.h"
#include "game_core.h"
#include "user_input.h"
#include "led_man.h"

/*
 * Routine for cycle animation of leds 
 */
void gameIntro(){
  Serial.println("Welcome to Led to Bag. Press Key TS to Start");
  int index = 0;
  int lstep = 1;
  switchObjLed(index, HIGH);   
  delay(50);
  
  int nlevels = getDifficultyLevel();
  #ifdef __DEBUG__
  Serial.println("DIFFICULTY LEVEL: "+String(nlevels));
  #endif

  while (!buttonTSpressed()){    
    switchObjLed(index, LOW);   
    index = (index + lstep);
    if (index > 2) {
      index = 1;
      lstep = -1;
    } else if (index < 0) {
      index = 1;
      lstep = 1;
    }
    switchObjLed(index, HIGH);   
    int newLevel = getDifficultyLevel();
    if (newLevel != nlevels){
      nlevels = newLevel;
      #ifdef __DEBUG__
      Serial.println("DIFFICULTY LEVEL: "+String(nlevels));
      #endif
    }
    delay(100);
  }  
  Serial.println("Go!");
}

void initGame(){
  resetLedBoard();  
  randomSeed(analogRead(0));
}

/*
 * Routine used in the game loop for managing
 * user input in bringing the obj to the bag
 */
bool bringObjToBag(int fromPos, long dt){
  int currentObjPos = fromPos;
  switchObjLed(currentObjPos,HIGH);
  
  long t0 = millis();
  long t = millis();
  bool objInBag = false;
  while (t - t0 < dt && !objInBag) {
    if (buttonTDpressed()){
      switchObjLed(currentObjPos,LOW);
      #ifdef __DEBUG__
      Serial.println("DOWN - "+String(currentObjPos));
      #endif
      if (currentObjPos > 0){
        currentObjPos = currentObjPos - 1;  
        switchObjLed(currentObjPos,HIGH);
      } else {
        pulseBagLed();
        objInBag = true;
      }
    }
    t = millis();
  }

  if (objInBag) {
     /* allow some small time for making mistakes */
     long t0 = millis();
     long t = millis();
     bool pressed = false;
     while (t - t0 < WRONG_INPUT_TIME && !pressed) {
        if (buttonTDpressed()){
           pressed = true;
        } else {
           t = millis();
        }
     }     
     switchBagLed(LOW);
     if (pressed){
       return false;
     } else {
       return true;
     }     
  } else {
    return false;
  }
}

/*
 *  GAME LOOP
 */
void gameLoop(){
  resetPlayerInput();

  int levels = getDifficultyLevel();
  /* computing the available time given the difficulty level */
  long dt = DT_MAX - DT_MAX_DELTA * getDifficultyLevel() / NLEVELS;
  Serial.println("Difficulty level: " + String(levels) + " time: " + dt);

  int score = 0;
  int currentPos = 2;

  while (true) {
    currentPos = random(0,3); 
    bool done = bringObjToBag(currentPos, dt);
    if (done){
      score++;
      Serial.println("Another object in the bag! Count: " + String(score) + " objects");
      dt = dt * DIFFICULTY_TIME_REDUCTION;
    } else {
      Serial.println("Game Over - Score: " + String(score));
      switchErrorLed(HIGH);
      delay(2000);
      switchErrorLed(LOW);
      break;
    }
  }
}
