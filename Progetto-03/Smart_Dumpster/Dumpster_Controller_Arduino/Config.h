#ifndef _CONFIG_H_
#define _CONFIG_H_

#define LED_V 13
#define LED_B 12
#define LED_G 11

#define SERVO 6
#define CHIUSO 10
#define APERTO 170

#define TX 2
#define RX 3

enum StateType{
    VERDE,
    BLU,
    GIALLO,
    EXTEND,
    CLOSED
};

#endif
