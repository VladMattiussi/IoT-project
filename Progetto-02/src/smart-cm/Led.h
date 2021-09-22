#ifndef __LED__
#define __LED__

class Led { 
public:
  Led(int pin);
  void switchOn();
  void switchOff();
  void blink();    
private:
  int pin;
  enum {ON, OFF} state;  
};

#endif
