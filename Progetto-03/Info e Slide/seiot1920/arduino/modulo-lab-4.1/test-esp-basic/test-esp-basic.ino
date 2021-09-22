/*
 * Note about ESP
 * 
 * - D2 <=> GPIO4
 * - boud rate: 115200
 */
#define LED_PIN 4

void setup() {                
  pinMode(LED_PIN, OUTPUT); 
  Serial.begin(115200);     
  Serial.println("READY"); 
}

void loop() {
  int value = analogRead(A0);
  Serial.println("Value: " + String(value));
  digitalWrite(LED_PIN, HIGH);
  Serial.println("ON");
  delay(500);             
  digitalWrite(LED_PIN, LOW);
  Serial.println("OFF");   
  delay(500);              
}
