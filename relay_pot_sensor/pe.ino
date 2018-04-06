/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/

// the setup routine runs once when you press reset:

//potpin A3
//sensorpin A1
//relay D8
//fan D9
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int potValue = analogRead(A3);
  int  sensorValue = analogRead(A1);
  int  sensorValueinside = analogRead(A2);
  float currentsensor = analogRead(A7);
  Serial.print("analogREAD curr = ");
  Serial.println(currentsensor);
float current= map(currentsensor,0.0,1023.0,-15.0,15.0);
  Serial.print("current = ");
  Serial.println(current);
  //Serial.print("analogREAD inside = ");
  //Serial.println(sensorValueinside);
  int newval=map(sensorValue,0,1023,1023,0);
  int newvalinside=map(sensorValueinside,0,1023,1023,0);
  int  temp=(int)2*((1/((log(((1164.0*(1023.0-newval))/newval)/75000.0)/3435.0)+(1/(273.15+27.0))))-273.15);
  int  tempinside=(int)((1/((log(((11640.0*(1023.0-newvalinside))/newvalinside)/8000.0)/3435.0)+(1/(273.15+27.0))))-273.15);
  Serial.print("BED = ");
  Serial.println(temp);
  Serial.print("BOX = ");
  Serial.println(tempinside);
  // print out the value you read:
  int settemp=map(potValue,0,1023,300,0);
  Serial.print("setemp = ");
  Serial.println(settemp);
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
  delay(1000);        // delay in between reads for stability
}
