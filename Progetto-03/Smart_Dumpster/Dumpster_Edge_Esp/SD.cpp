#include "SD.h"
void SD::changeState(bool state){
    this->state = state;
    
    if(this->state){
        this->ledR->switchOff();
        this->ledV->switchOn();
    }
    else{
        this->ledV->switchOff();
        this->ledR->switchOn();
    }
}

SD::SD(int ledV, int ledR, int pot,bool state) { 
	this->ledV = new Led(ledV);
    this->ledR = new Led(ledR);
    this->pot = new Potentiometer(pot);
    this->current = 0;
    this->state = state;
}

int SD::getDumpsterCapacity() {
  return this->pot->getMappedValue(START,MAX);
}
int SD::update() {
    if(this->checkState()){
        int dumpsterCapacity = getDumpsterCapacity();
        if(this->current != dumpsterCapacity){
            this->current = dumpsterCapacity;
            Serial.print("valore potenziometro: ");
            Serial.println(this->current);
            
            if(this->current >= MAX){
                this->changeState(false);
            }
            return this->current;
        }
    }
    return -1;
}

bool SD::checkState() {
    return this->state;
}

int SD::getSpaceLeft() {
    int capacity = MAX;
    return capacity-this->current;
}
