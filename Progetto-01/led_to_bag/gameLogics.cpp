#include "gameLogics.h"
#include "Arduino.h"
#include "MiniTimerOne.h"
#include "utility.h"

int btn[] = {LEDG1, LEDG2, LEDG3, LEDW1}; //array containing all the led
int on;   //this variable contains the "on" led at any given moment
int score;  //score of the player, each game

long levelTime;
bool firstTimer;
bool playing;  //flag. Tracks the game status, true if the player is playing

unsigned long lastDebounceTime;
unsigned long lastFade;

unsigned long lastTime;
int currIntensity;

int fadeAmount = 5;

void standby() {
  int inc = 1;  //used to make the standby effect
  unsigned long lastBlinkTime = 0;
  EIFR = (1 << INTF1);
  attachInterrupt(digitalPinToInterrupt(BUTTONSTART), startGame, RISING);
  while (!playing) {
    if (millis() - lastBlinkTime > BLINK_TIME) {
      light(on);
      on += inc;
      if (on == 2 || on == 0) {
        inc = -inc;
      }
      lastBlinkTime = millis();
    }
  }
  detachInterrupt(digitalPinToInterrupt(BUTTONSTART));
  turnOffAll();
}

void gameloop() {
  bool roundStart = false; //flag. True after the first round, resets each game
  bool startCounting = false;  //flag. True when start the player reaches LEDW1
  while (playing) {
    if (!roundStart) {
      initRound();
      roundStart = true;
    }
    if (on == 3) {  //win condition, needs to stay in this cycle for "BAG_TIME" ms
      if (!startCounting) {
        MiniTimer1.stop();
        lastTime = millis();
        startCounting = true;
      }
      fading();
      if (millis() - lastTime > BAG_TIME) {
        score++;
        roundStart = false;
        startCounting = false;
        digitalWrite(LEDW1, LOW);
        Serial.print("Another object in the bag! Count:");
        Serial.print(score);
        Serial.println(" objects");
      }
    }
    if (on == 4) {    //lose condition
      gameover();
    }
  }
  turnOffAll();                           //lose animation
  Serial.print("Game Over - Score: ");
  Serial.println(score);
  digitalWrite(LEDR1, HIGH);
  delay(LEDR1_ON_TIME);
  digitalWrite(LEDR1, LOW);
}

void initRound() {
  on = random(3);
  light(on);
  digitalWrite(LEDW1, LOW); //...bug-solver (the yellow red remains lit after attaching TD interrupt)
  firstTimer = false;
  if (score > 0) {
    levelTime = (levelTime * 7) / 8;
  }
  MiniTimer1.setPeriod(levelTime);
  MiniTimer1.reset();
  MiniTimer1.start();
}

void timeUpRoutine() {
  if (!firstTimer) {
    //Serial.println("timer1 UP");
    MiniTimer1.reset();
    firstTimer = true;
  }
  else
  {
    firstTimer = false;
    Serial.println("time up");
    gameover();
  }
}

void gameover() {
  playing = false;
  detachInterrupt(digitalPinToInterrupt(BUTTONDOWN));
  MiniTimer1.stop();
}

void startGame() {
  playing = true;
}
void down() {
  if ((millis() - lastDebounceTime) > DEBOUNCE_TIME) {
    lastDebounceTime = millis();
    digitalWrite(btn[on + 1], HIGH);
    digitalWrite(btn[on], LOW);
    on++;
    //Serial.println("DOWN PRESSED");
  }
}

void readDifficulty() {
  EIFR = ( 1 << INTF0);
  attachInterrupt(digitalPinToInterrupt(BUTTONDOWN), down, RISING);
  int difficulty = map(analogRead(POTENZIOMETRO), 0, 1023, 1, 8);
  levelTime = (BASE_LEVEL_TIME / difficulty) / 2;
}

void reset() {
  lastFade = 0;
  lastDebounceTime = 0;
  playing = false;
  score = 0;
  on = 0;
}
