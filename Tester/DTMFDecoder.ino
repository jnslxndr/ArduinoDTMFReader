/*
  Parse Result from the DTMF decoder chip to an int
 */
#include <avr/pgmspace.h>

// #define DEBUG 0

// Store the DTMF key table in Flash memory
PROGMEM  prog_uchar dtmf_keys[]  = { 
  'D','1','2','3','4','5','6','7','8','9','0','*','#','A','B','C'
};

const char NO_DTMF_AVAIL = -1;
volatile char DTMF_CODE = NO_DTMF_AVAIL;

void setup_dtmf_reader(){
  prepare_dtmf_reader();
  // Attach the decoder to interrupt pin 3
  attachInterrupt(1,read_dtmf_on_detection,RISING);
}

void prepare_dtmf_reader() {
  DDRC  = (DDRC >> 4) << 4; // Set all as Inputs
  PORTC = PINC&B11110000; // and turn them down
}

// Interrupt Callback function
void read_dtmf_on_detection(){
  dtmf_get_code(&DTMF_CODE); // parse directly from Port
}

// Decoding function
void dtmf_get_code(volatile char *code) {
  *code = dtmf_get_key_at_index(PINC & B00001111);
}

char dtmf_get_key_at_index(int index) {
  return pgm_read_byte_near(dtmf_keys+index); // pick the char from the progmem
}

boolean dtmf_available(){
  return DTMF_CODE != NO_DTMF_AVAIL;
}

char dtmf_read(){
  char _current = DTMF_CODE; 
  DTMF_CODE = NO_DTMF_AVAIL;
  return _current;
}



