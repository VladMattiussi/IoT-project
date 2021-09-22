#ifndef __CONFIG__
#define __CONFIG__

/* RADAR */

#define RADAR_TRIG_PIN 7
#define RADAR_ECHO_PIN 8
#define RADAR_SERVO_PIN 3

#define SCAN_TIME_MIN 1000
#define SCAN_TIME_MAX 10000 

#define LD_PIN 4
#define LA_PIN 5 

#define BUTTON_TM1_PIN 10
#define BUTTON_TM2_PIN 12
#define BUTTON_TM3_PIN 13

#define PIR_PIN 2

#define NUM_SECTORS 16

#define DNEAR 0.10
#define DFAR 0.30

#define SONAR_MAX_DIST 1

#define POT_PIN A0



#endif
