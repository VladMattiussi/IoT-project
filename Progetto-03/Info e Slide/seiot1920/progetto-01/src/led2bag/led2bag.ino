/*
 * SEIOT a.a. 2019/2020
 *
 * PROGETTO #1 - LED 2 BAG
 * 
 * Esempio di soluzione.
 */
#include "config.h"
#include "game_core.h"
#include "user_input.h"
#include "led_man.h"

void setup() {
  Serial.begin(9600);
  initLedBoard();
  initPlayerInput();
}

void loop(){  
  gameIntro();
  initGame();
  gameLoop();
}
