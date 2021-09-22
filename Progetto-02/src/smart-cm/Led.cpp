#include "Led.h"
#include "Arduino.h"

Led::Led(int pin){
  this->pin = pin;
  this->state = OFF;
  pinMode(pin,OUTPUT);
}

void Led::switchOn(){
  digitalWrite(pin,HIGH);
}

void Led::switchOff(){
  digitalWrite(pin,LOW);
};

void Led::blink(){
  if(this->state==OFF){
    this->switchOn();
    this->state=ON;
  }
  else{
    this->switchOff();
    this->state=OFF;
  }
}
