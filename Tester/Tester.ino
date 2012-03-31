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
  
  // Test DTMF
  // softSerial.println("AT+CLDTMF=1,\"1,2,3,4,5,6,7,8,9,0,\\*,#,A,B,C,D\"");
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


