#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

Adafruit_PCD8544 display = Adafruit_PCD8544(3, 4, 5, 6, 7);
int potValue=0;
int settemp=0;
int timed=0;
void setup() {
  Serial.begin(9600);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,INPUT);
  pinMode(11,INPUT);
  pinMode(12,INPUT);
  display.begin();
  display.setContrast(60);
  display.clearDisplay(); 

  display.clearDisplay();  
  display.setTextSize(3);
  display.setTextColor(BLACK);
  display.setCursor(1,5);
  display.println("B");
  display.setCursor(22,15);
  display.setTextSize(1);
  display.println("- AUTOMATE");
  display.setCursor(1,30);
  display.println("Automating");
  display.setCursor(47,39);
  display.println("lives");
  display.display(); // show splashscreen
  delay(5000);
  potValue = analogRead(A3);
  settemp=map(potValue,0,1023,300,0);
}

void loop() {
if(digitalRead(11)==HIGH)
{  int count=0;
  while(1)
   {
    
  potValue = analogRead(A3);
  settemp=map(potValue,0,1023,300,0);
  display.clearDisplay();  
  display.setTextSize(2);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  display.print("SET:");
  display.println(settemp);
  Serial.print("setemp = ");
  Serial.println(settemp);
  display.display(); 
 
  if(count==0)
  {
    timed=2000;
    count=1;
  }
  else
  {
     timed=10;
  }
  delay(timed);
  if(digitalRead(11)==HIGH)
  {
    break;
  }
}
} 
  int  sensorValue = analogRead(A1);
  int  sensorValueinside = analogRead(A2);
  float currentsensor = analogRead(A7);
  float current= map(currentsensor,0.0,1023.0,-15.0,15.0);
  int power = (current*12);
  if(power<0)
  {
    power=0;
  }
  int newval=map(sensorValue,0,1023,1023,0);
  int newvalinside=map(sensorValueinside,0,1023,1023,0);
  int  temp=(int)2*((1/((log(((1164.0*(1023.0-newval))/newval)/75000.0)/3435.0)+(1/(273.15+27.0))))-273.15);
  int  tempinside=(int)((1/((log(((11640.0*(1023.0-newvalinside))/newvalinside)/8000.0)/3435.0)+(1/(273.15+27.0))))-273.15);
  Serial.print("BED = ");
  Serial.println(temp);
  Serial.print("BOX = ");
  Serial.println(tempinside);
  // print out the value you read:
  
  if(temp>settemp+10)
  {
    digitalWrite(8,LOW);
  }
  else if(temp<settemp)
  {
    digitalWrite(8,HIGH);
  }
  if(tempinside>30)
  {
    digitalWrite(9,LOW);
  }
  else if(tempinside<30)
  {
    digitalWrite(9,HIGH);
  }
  

  display.clearDisplay();  
  display.setTextSize(2);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  display.print("SET:");
  display.println(settemp);
  display.print("BED:");
  display.println(temp);
  display.print("BOX:");
  display.println(tempinside);
  display.display(); 
  delay(2000);
  display.clearDisplay();  
  display.setTextSize(2);
  display.setTextColor(BLACK);
  display.setCursor(12,0);
  display.print("POWER");
  display.setTextSize(3);
  display.setTextColor(BLACK); 
  if(power>0)
  {
  display.setCursor(5,25);
  
  }
  else
  {
    display.setCursor(25,25);
  }
  
  display.print(power);
  display.println("W");
  
  display.display(); 
  delay(2000);
}
