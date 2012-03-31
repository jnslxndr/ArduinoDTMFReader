/*
  Parse Result from the DTMF decoder chip to an int
 */

char DTMF_CODE = -1;

// Interrupt Callback function
void decode_on_detection(){
  DMTF_CODE = decode_dtmf(PORTB); // decode directly from Port
}

// Decoding function
char decode_dtmf(int PORT) {
  
}
