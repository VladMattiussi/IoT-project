#include "PrintTask.h"
#include "Arduino.h"

PrintTask::PrintTask(){
}
  
void PrintTask::init(int period){
  Task::init(period);
  count = 0;
}
  
void PrintTask::tick(){
  count++;
  // if (count % 10 == 0){
    Serial.println("fire " + String(count) + " millis: " + String(millis()));
  // }
}
