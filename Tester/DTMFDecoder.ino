/*
  Parse Result from the DTMF decoder chip to an int
 */
#include <avr/pgmspace.h>

// save some unsigned ints
PROGMEM  prog_uchar dtmf_keys[]  = { 
  'D','1','2','3','4','5','6','7','8','9','0','*','#','A','B','C'
};

const char NO_DTMF_AVAIL = -1;
volatile char DTMF_CODE = NO_DTMF_AVAIL;
volatile uint8_t* DTMF_PORT = -1;

void setup_dtmf_reader(PORT){
  DTMF_PORT = PORT;
  prepare_dtmf_reader(DTMF_PORT);
  // Attach the decoder to interrupt pin 3
  attachInterrupt(1,read_dtmf_on_detection,RISING);
}

void prepare_dtmf_reader() {
  DDRC  = (DDRC >> 4) << 4; // Set all as Inputs
  PORTC = PINC&B11110000; // and turn them down
}

// Interrupt Callback function
void read_dtmf_on_detection(){
  DTMF_CODE = parse_dtmf(); // parse directly from Port
}

// Decoding function
char parse_dtmf() {
  int _key_pos = PINC & B00001111; // we need 4 pins
  return pgm_read_byte_near(dtmf_keys+_key_pos); // pick the char from the progmem
}

boolean dtmf_available(){
  return DTMF_CODE != NO_DTMF_AVAIL;
}

char dtmf_read(){
  char _current = DTMF_CODE; 
  DTMF_CODE = NO_DTMF_AVAIL;
  return _current;
}



