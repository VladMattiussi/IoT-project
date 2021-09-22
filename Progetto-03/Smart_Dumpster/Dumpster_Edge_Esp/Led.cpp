#include "Led.h"

Led::Led(unsigned int pin){
  isOn = false;
  this->pin = pin;
  pinMode(this->pin,OUTPUT);
}
void Led::switchOn() {
  this->isOn = true;
  digitalWrite(this->pin,HIGH);
}
void Led::switchOff() {
  this->isOn = false;
  digitalWrite(this->pin,LOW);
}
void Led::setBrightness(unsigned int value) {
  const unsigned int toBeWritten = value > Led::ANALOG_MAX ? Led::ANALOG_MAX : value;
  this->isOn = value > 0 ? true : false;
  analogWrite(this->pin,toBeWritten);
}

bool Led::isActive(){
  return this->isOn;
}
