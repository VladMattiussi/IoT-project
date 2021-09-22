#ifndef _POTENTIOMETER_H_
#define _POTENTIOMETER_H_
/* It models a potentiometer sensor, with methods for receive the current value expressed
with analogRead or map the value read in a specified interval */
#include "Arduino.h"

class Potentiometer{
    private:
        static const unsigned int ANALOG_MIN = 0;
        static const unsigned int ANALOG_MAX = 1023;
        unsigned int pin;
    public: 
        Potentiometer(unsigned int pin);
        unsigned int getValue();
        long getMappedValue(long out_min, long out_max);
};
#endif
