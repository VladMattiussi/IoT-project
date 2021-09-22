#ifndef __LED_MAN__
#define __LED_MAN__

void initLedBoard();
void resetLedBoard();
void switchObjLed(int pos, int state);
void switchBagLed(int state);
void pulseBagLed();
void switchErrorLed(int state);

#endif
