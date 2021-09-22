#ifndef __TASK__
#define __TASK__
#define N_OF_MODES 3
//ID Tasks
#define SINGLE_TASK 0
#define MANUAL_TASK 1
#define AUTO_TASK 2
#define INPUT_TASK 3
#define BLINK_TASK 4


class Task {
  int myPeriod;
  int timeElapsed;
  
public:
  virtual void init(int period){
    myPeriod = period;  
    timeElapsed = 0;
  }

  virtual void tick() = 0;

  bool updateAndCheckTime(int basePeriod){
    timeElapsed += basePeriod;
    if (timeElapsed >= myPeriod){
      timeElapsed = 0;
      return true;
    } else {
      return false; 
    }
  }
  
};

#endif
