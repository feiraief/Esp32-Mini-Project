//pin
#define pinRelay 6 //Change relay pin 
#define pinMoisture A0 // Change Moisture sensor pin

unsigned long PrevMillis = 0;
const long interval = 1000;

int soilAnalog;
int Moisture;

enum Pump {PUMP_OFF, PUMP_ON, Sleep};
Pump pumpState = PUMP_OFF;

void setup() {
  Serial.begin(115200);
  pinMode(pinMoisture, INPUT);
  pinMode(pinRelay, OUTPUT);
  digitalWrite(pinRelay, HIGH);

}
void loop() {
  unsigned long CurrentMillis = millis();
  if(CurrentMillis - PrevMillis >= interval){
    MoistureSensor();
    PrevMillis = CurrentMillis;
  } 
  ActionPump();
}
void ActionPump(){
  switch(pumpState){
    case PUMP_OFF:
      if(Moisture <= 50){
        Serial.println("Pump = ON");
        digitalWrite(pinRelay,LOW);
        pumpState = PUMP_ON;
      }
    break;
    case PUMP_ON:
      if(Moisture > 51){
        Serial.println("Pump = OFF");
        digitalWrite(pinRelay,HIGH);
        pumpState = PUMP_OFF;
      }
  }
}
void MoistureSensor(){
  soilAnalog = analogRead(pinMoisture);
  soilAnalog = random(4096);
  Moisture = map(soilAnalog, 0, 4095, 100, 0);
  Serial.print("Moisture : ");
  Serial.print(soilAnalog);
  Serial.print(" - ");
  Serial.print(Moisture);
  Serial.println("%");
}