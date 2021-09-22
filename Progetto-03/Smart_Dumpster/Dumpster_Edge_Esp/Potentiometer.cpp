#include "Potentiometer.h"

Potentiometer::Potentiometer(unsigned int pin){
    this->pin = pin;
    pinMode(this->pin,INPUT);
}
unsigned int Potentiometer::getValue(){
    return analogRead(this->pin);
}
long Potentiometer::getMappedValue(long out_min, long out_max){
    return map(this->getValue(),Potentiometer::ANALOG_MIN,Potentiometer::ANALOG_MAX,out_min,out_max);
}
