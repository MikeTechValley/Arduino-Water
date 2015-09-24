#include <LiquidCrystal.h>

#define runEvery(t) for (static uint16_t _lasttime;\
                         (uint16_t)((uint16_t)millis() - _lasttime) >= (t);\
                         _lasttime += (t))

#define SENSOR A0
int sensors = 4;
int moistValue[4];
byte relayPin[4] = {2,7,8,10};
int potPin = 4;
int water[4] = {0,0,0,0}; //set water flow off
long interval = 1000; 
int potval;
int moistDiff;

LiquidCrystal lcd(12, 11, 5, 4, 3, 6);

void setup() {
  Serial.begin(9600);
  Serial.println("SOIL MOISTURE SENSOR DEMO");
  for(int i = 0; i < 4; i++)  pinMode(relayPin[i],OUTPUT);
  lcd.begin(20, 4);
        
}

void loop() {
  lcd.clear();
  potval = analogRead(potPin);
  for (int ii=0;ii<sensors;ii++) {
    moistValue[ii] = analogRead(ii);
    Serial.print("Potentiometer level: ");
    Serial.print(potval);
    Serial.println(" ");
    Serial.print("MOISTURE LEVEL : ");
    Serial.print(ii);
    Serial.print(" ");
    Serial.print(moistValue[ii]);
    Serial.println("  ");
          
    while (moistValue[ii] > potval) {
      Serial.println("needs water");
      lcd.setCursor(0, 0);
      lcd.print("Watering Plant #");
      lcd.print(ii+1);
      lcd.setCursor(0, 1);
      lcd.print("Moisture: ");
      lcd.print(moistValue[ii]);
      lcd.setCursor(0, 2);
      lcd.print("Potentiometer: ");
      lcd.print(potval);
      
      if (water[ii]==0) {
        Serial.println("turning on water");
        Serial.println("opening relay");
        water[ii]=1;
        digitalWrite(relayPin[ii], HIGH);
      }
    }
           
  
    if(moistValue[ii] <= potval) {
      Serial.println("water level OK");
      lcd.setCursor(0, 0);
      lcd.print("Plant #");
      lcd.print(ii+1);
      lcd.print(" Moisture OK.");
      lcd.setCursor(0, 1);
      lcd.print("Moisture: ");
      lcd.print(moistValue[ii]);
      lcd.setCursor(0, 2);
      lcd.print("Potentiometer: ");
      lcd.print(potval);
      
      if (water[ii]==1) {
        Serial.println("Turning Off Water");
        Serial.println("Closing relay");
        water[ii]=0;
        digitalWrite(relayPin[ii], LOW);
      }
    }
    delay(5000);
  }

//delay(5000);

}
