#include "SD.h"
#include "servo_motor_impl.h"

SD::SD(int led_v, int led_b, int led_g,int servo) { 

	this->ledV = new Led(led_v);
    this->ledB = new Led(led_b);
    this->ledG = new Led(led_g);
    
    this->servo = new ServoMotorImpl(servo);;
    this->servo->on();
    this->servo->setPosition(CHIUSO);
    this->state = CLOSED;
    this->timer = TIME+millis();
}
void SD::discharge(StateType state) {

    if(state == EXTEND){
      this->timer += TIME;  
      return;
    }

    if(this->state != state){
        this->close(this->state);
    }

    if(this->state == CLOSED){
        this->state = state;
        Serial.print("stato:");
        Serial.println(this->state);
        this->timer = TIME + millis();
        switch (state){
        case VERDE:
            this->ledV->switchOn();
            break;
        case GIALLO:
            this->ledB->switchOn();
            break;
        case BLU:
            this->ledG->switchOn();
            break;
        default:
            break;
        }
        Serial.println("apertura servo");
        this->servo->setPosition(APERTO);
        Serial.println("Servo aperto");
      
    }
    return;
}
void SD::close(StateType state){

	  /*switch (state){
        case VERDE:
            this->ledV->switchOff();
            break;
        case BLU:
            this->ledB->switchOff();
            break;
        case GIALLO:
            this->ledG->switchOff();
            break;
        default:
            break;
    }*/
    //
    
    
    if(this->state!= CLOSED){
      Serial.print("Chiusura servo");
      this->ledG->switchOff();
      this->ledV->switchOff();
      this->ledB->switchOff();
      this->state = CLOSED;
      this->servo->setPosition(CHIUSO);
      Serial.print("Servo chiuso");
    }
}

void SD::check(){

  if(millis()>=this->timer){
     this->close(this->state);
  }
}
