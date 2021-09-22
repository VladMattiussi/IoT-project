#ifndef _SD_H_
#define _SD_H_

#include "Led.h" 
#include "Potentiometer.h"

#define START 0
#define MAX 100

class SD{  
  /* Come campi privati uso i 2 led, il potenziometro, 
  salvo lo stato e creo anche una funzione per cambiarlo*/
	private:
	  Led* ledV;
    Led* ledR;
    Potentiometer* pot;
    int current;
    bool state;
    
    int getDumpsterCapacity();
  /* Ho il costruttore, una funzione per scaricare e una per verificare lo stato*/
	public:  
	SD(int ledV, int ledR, int pot,bool state);
	  int update();
    bool checkState();
    int getSpaceLeft();
    void changeState(bool state);
};
#endif
