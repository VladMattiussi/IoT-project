#ifndef _SD_H_
#define _SD_H_

#include "Led.h" 
#include "servo_motor_impl.h"
#include "Config.h"

#define TIME 10000

class SD{  
	private:
        StateType state;
	Led* ledV;
        Led* ledB;
        Led* ledG;
        ServoMotor* servo;
        unsigned long timer;
        void close(StateType type);
	public:  
	SD(int led_v, int led_b, int led_g,int servo);
	void discharge(StateType type);
  void check();
};
#endif
