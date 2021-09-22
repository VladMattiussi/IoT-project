#include "gameLogics.h"
#include "utility.h"
#include "MiniTimerOne.h"

void setup() {
  Serial.begin(9600);

  pinMode(LEDG1, OUTPUT);
  pinMode(LEDG2, OUTPUT);
  pinMode(LEDG3, OUTPUT);
  pinMode(LEDW1, OUTPUT);
  pinMode(LEDR1, OUTPUT);

  pinMode(BUTTONDOWN, INPUT);
  pinMode(BUTTONSTART, INPUT);
  pinMode(POTENZIOMETRO, INPUT);
  randomSeed(analogRead(0));
  MiniTimer1.init();
  MiniTimer1.attachInterrupt(timeUpRoutine);
}

void loop() {
  Serial.println("Welcome to Led to Bag. Press Key TS to Start!");
  standby();
  delay(TIME_BEFORE_STARTING);
  Serial.println("Go!");
  readDifficulty();
  gameloop();
  reset();
}
