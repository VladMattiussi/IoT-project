/* Attenzione: RIcorda di mettere la mcu 0.9 di SD8266 da strumenti->scheda */
#include <ESP8266mDNS.h>
#include <ESP8266mDNS_Legacy.h>
#include <LEAmDNS.h>
#include <LEAmDNS_lwIPdefs.h>
#include <LEAmDNS_Priv.h>
/* Attenzione: Installa la libreria "ArduinoJson" dal Strumenti->Gestione librerie */
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

#include "Config.h"
#include "SD.h"

/* wifi network name */
char* netName = "TIM2.4";
/* WPA2 PSK password */
char* pwd = "aNq6bmtc";
/* service IP address */
char* address = /*"http://192.168.1.9:80/smartdumpster";*/"http://fc5dbb7b.ngrok.io/iot/dashboard";
SD* dumpster;
  
int requestStatus(String address){
   
   HTTPClient http;
   http.begin(address + "/richieste.php/?request=state");
   int retCode = http.GET();
   if (retCode != 200){
    return ERR;
   }
   String status = http.getString();
   int state = status.toInt();
   http.end();
   return state;
  }
  
  int sendData(String address, int val, int stato, int spaceLeft){
   HTTPClient http;
   http.begin(address + "/richieste.php/?state=" + stato + "&capacity=" + val + "&sleft=" + spaceLeft);
   int retCode = http.GET();
   Serial.print("contenuto retCode:");
   Serial.println(retCode);
   if (retCode != 200){
    return ERR;
   }
   http.end();
   return 0;
  }

void setup() {
  Serial.begin(115200);
  WiFi.begin(netName, pwd);
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  } 
   int state = requestStatus(address);
   if(state!=ERR){
    dumpster = new SD(LED_V,LED_R,POT,state);
   }

}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("wifi: connesso");

    int state = requestStatus(address);
    dumpster->changeState(state);
    Serial.print("dumpster service : ");
    Serial.println(state);
    if(state!=ERR){
      int val = dumpster->update();
      Serial.print("dumpster value : ");
      Serial.println(val);
      if(val!=ERR){ //se val == -1 allora non fai niente, altrimenti sendData
        int spaceLeft = dumpster->getSpaceLeft();
        int stato = dumpster->checkState();
        int res = sendData(address, val, stato, spaceLeft);
        if(res==ERR) {
          Serial.println("errore di connessione");
        }
        Serial.println("sending.....");
        Serial.print("dumpster spaceLeft : ");
        Serial.println(spaceLeft);
        Serial.print("dumpster state : ");
        Serial.println(stato);
      }  
    }
  } else {
    Serial.println("ERR in WiFi connection");
  }
  delay(10000); //1 azione ogni 10 secondi
}
