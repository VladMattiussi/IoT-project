#ifndef _LED_H_
#define _LED_H_

/* It models a simple led with methods for switching off and on, setting a specific 
  brightness or knowing if the led is active or not*/
#include "Arduino.h"

class Led {
  private:
    static const unsigned int ANALOG_MIN = 0;
    static const unsigned int ANALOG_MAX = 1023;
    unsigned int pin;
    bool isOn;
  public:
    Led(unsigned int pin);
    virtual void switchOn();
    virtual void switchOff();
    virtual void setBrightness(unsigned int value);
    virtual bool isActive();
};
#endif
