#include "Arduino.h"
#include "utility.h"
extern int btn[];
extern unsigned long lastFade;
extern int fadeAmount;
extern int currIntensity;

void turnOffAll() {
  digitalWrite(LEDG1, LOW);
  digitalWrite(LEDG2, LOW);
  digitalWrite(LEDG3, LOW);
  digitalWrite(LEDW1, LOW);
}

void fading() {
  unsigned long currentFadeTime = millis();
  if (currentFadeTime - lastFade > FADE_SPEED) {
    analogWrite(LEDW1, currIntensity);
    currIntensity = currIntensity + fadeAmount;
    lastFade = currentFadeTime;
    if (currIntensity == 0 || currIntensity == 255) {
      fadeAmount = -fadeAmount ;
    }
  }
}

void light(int a) {
  digitalWrite(btn[a], HIGH);
  digitalWrite(btn[(a + 1) % 3], LOW);
  digitalWrite(btn[(a + 2) % 3], LOW);
}
