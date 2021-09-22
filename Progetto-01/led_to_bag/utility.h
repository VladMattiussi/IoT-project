#ifndef UTILITY_H
#define UTILITY_H
#define LEDG1 13
#define LEDG2 12
#define LEDG3 11
#define LEDW1 6
#define LEDR1 8
#define POTENZIOMETRO A0

#define BUTTONDOWN 2
#define BUTTONSTART 3

#define BASE_LEVEL_TIME 8000000L //Base starting time (8s)
#define BLINK_TIME 100 //Standby blink time
#define DEBOUNCE_TIME 134 //debounce waiting time (134 for me)
#define BAG_TIME 1800 //time in the bag
#define FADE_SPEED 5 //delay(5)
#define TIME_BEFORE_STARTING 500 //time(ms) before the game starts after button press
#define LEDR1_ON_TIME 2000 //time(ms) before the game starts after game over
/*
 * turn all the lights off (except the red led)
 */
void turnOffAll();

/*
 * logics about the animation of the item in the bag
 */
void fading();

/*
 * Lights the led that is in 'a' position
 */
void light(int a);
#endif
