/*
 *  This header file stores symbols that concerns 
 *  the configuration of the system.
 *
 */
#ifndef __CONFIG__
#define __CONFIG__

#define __DEBUG__

#define LED01_PIN 12
#define LED02_PIN 11
#define LED03_PIN 10

#define LEDBAG_PIN 9
#define LEDERROR_PIN 8

#define TS_PIN 3
#define TD_PIN 2

#define BOUNCING_TIME_TS 120
#define BOUNCING_TIME_TD 120

#define WRONG_INPUT_TIME 400
#define DIFFICULTY_TIME_REDUCTION 0.75
#define DT_MAX 4000
#define DT_MAX_DELTA 3000
#define NLEVELS 8
#define POT_PIN A0

#endif
