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
  
  setup_dtmf_reader();
}

void loop()
{
  if (dtmf_available()) {
    Serial.print("DTMF: ");
    Serial.println(dtmf_read());
  }
  if (softSerial.available())
    Serial.write(softSerial.read());
  if (Serial.available())
    softSerial.write(Serial.read());
}


