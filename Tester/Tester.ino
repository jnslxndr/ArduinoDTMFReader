/*
  A simple Serial proxy from hardware Serial to SoftwareSerial
 */

#include <SoftwareSerial.h>

#define rxPin 7
#define txPin 8

SoftwareSerial softSerial(rxPin,txPin); 

void setup()
{
  softSerial.begin(19200);               // the GPRS baud rate   
  Serial.begin(19200);                 // the GPRS baud rate   
}

void loop()
{
  if (softSerial.available())
    Serial.write(softSerial.read());
  if (Serial.available())
    softSerial.write(Serial.read());  
}


