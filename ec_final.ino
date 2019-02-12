#include <LiquidCrystal.h>
#include<dht.h>
dht DHT;
#define dht11 A0   //temp and humidity
int lm393 = 8;     //light sensor
int kg003 = A2;    //soil moisture sensor
int output;       //soil moisture output
int relay1 = 14;  //bulb switch
int relay2 = 15;  //exhaust switch
int relay3 = 16;  //pump switch
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // rs,en,d4,d5,d6,d7

void setup() {
  pinMode(lm393,INPUT);
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);
  lcd.begin(16,2);
  Serial.begin(9600);
  Serial.println("CLEARDATA");     //plx daq initiate(excel)
  Serial.println("LABEL,Temp,Humidity,Moisture"); 
  Serial.println("RESETTIMER"); 

}

void loop() {
  DHT.read11(dht11);
  output=analogRead(kg003);
  output=map(output,1021,505,0,100);   //set value of soil moisture in between 0 to 100%
  Serial.print("DATA,Temp");           //display on excel
  Serial.print(DHT.temperature);
  Serial.print("DATA,Humidity");
  Serial.print(DHT.humidity);
  Serial.print("DATA,Moisture");
  Serial.print(output);
  Serial.println("% ");
  Serial.println("..."); 
  delay(2000); 
  lcd.clear();
  lcd.setCursor(0,0);                  //display lcd
  lcd.print("Humidity = ");
  lcd.print(DHT.humidity);
  lcd.setCursor(0,1);
  lcd.print("Temp = ");
  lcd.print(DHT.temperature);
  //delay(2000); 
  if(DHT.temperature>25||DHT.humidity>60)
  {digitalWrite(relay2,HIGH);}
  else
  {digitalWrite(relay2,LOW);}
  if(output<20)
  {digitalWrite(relay3,HIGH);}
  else
  {digitalWrite(relay3,LOW);}
  int ldr = digitalRead (lm393);
  if(ldr==1)
  {
    digitalWrite(relay1,HIGH);
  }
  else
  {
    digitalWrite(relay1,LOW);
  }
  //delay(2000);
}
