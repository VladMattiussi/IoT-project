#include "counter.h"

Counter c(10);
Counter* c1;

void setup(){
  Serial.begin(9600); 
  c1 = new Counter(20);
}

void loop(){
  c.inc();
  Serial.println(c.getValue());
  c1->inc();
  Serial.println(c1->getValue());
  delay(1000);
}

