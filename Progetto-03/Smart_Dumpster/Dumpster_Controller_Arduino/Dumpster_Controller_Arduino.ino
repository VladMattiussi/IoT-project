#include <SoftwareSerial.h>
#include "Config.h"
#include "SD.h"

#define DELAY 1000

SoftwareSerial btChannel(TX, RX);
SD* dumpster;
int i;
void setup() {
  btChannel.begin(9600);
  Serial.begin(9600);
  dumpster = new SD(LED_V,LED_B,LED_G,SERVO);
  i = 0;
}

void loop() {
  StateType input;
  if(btChannel.available()){
    String tmp = btChannel.readString();
    input = commandConverter(tmp);
    Serial.print("Dato ricevuto: ");
    Serial.println(tmp);
    Serial.print("Dato convertito: ");
    Serial.println(input);
    dumpster->discharge(input);
  }
  //dumpster->discharge(commandConverter("C"));
  dumpster->check();
  delay(100);
  

} 

StateType commandConverter(String command){
  Serial.print("Dentro commandConverter:");
  Serial.println(command);
  if(command == "A\n"){
      return VERDE;
  }else if(command == "C\n"){
      return BLU;
  }else if(command == "B\n"){
      return GIALLO;
  }else if(command == "E\n"){
      return EXTEND;
  }else{
      return CLOSED;
  }
}
