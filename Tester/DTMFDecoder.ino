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
static int DTMF_USE_IRQ = true;
volatile char DTMF_CODE = NO_DTMF_AVAIL;

void set_dtmf_reader_to_use_interrupts(boolean yepnope) {
  DTMF_USE_IRQ = yepnope;
}

void setup_dtmf_reader(){
  prepare_dtmf_reader();
  // Attach the decoder to interrupt pin 3
  if (DTMF_USE_IRQ) {
    attachInterrupt(1,read_dtmf_on_detection,RISING);
  }
}

const int DTMF_CODE_PINS = B00111100;
const int DTMF_CODE_PIN_POS = 2;
const int DTMF_STATE_PIN = B01000000;
const int DTMF_STATE_PIN_POS = 6;
const int DTMF_PINS = DTMF_CODE_PINS | DTMF_STATE_PIN;

void prepare_dtmf_reader() {
  DDRD  = DDRD & ~DTMF_PINS;
  PORTD = PIND & ~DTMF_PINS;  //enable pull up resistor?
}

// Interrupt Callback function
void read_dtmf_on_detection(){
  dtmf_get_code(&DTMF_CODE); // parse directly from Port
}

int dtmf_get_state() {
  return (PIND & DTMF_STATE_PIN) >> DTMF_STATE_PIN_POS;
}

// Decoding function
void dtmf_get_code(volatile char *code) {
  *code = dtmf_get_key_at_index((PIND & DTMF_CODE_PINS) >> DTMF_CODE_PIN_POS);
  #ifdef DEBUG
  Serial.print("Decoded: "); Serial.println(*code);
  #endif
}

char dtmf_get_key_at_index(int index) {
  #ifdef DEBUG
  Serial.print("Index wanted: "); Serial.println(index);
  #endif
  return pgm_read_byte_near(dtmf_keys+index); // pick the char from the progmem
}

int dtmf_state_changed(){
  static int DTMF_LAST_STATE;
  int state = dtmf_get_state();
  int out = 0;
  if (DTMF_LAST_STATE != state) {
    #ifdef DEBUG
    Serial.print("State Pin: "); Serial.println(state);
    #endif
    out = state > DTMF_LAST_STATE && state==1 ? 1 : -1; // 1 == RISING, -1 == FALLING
  }
  DTMF_LAST_STATE = state;
  return out;
}

boolean dtmf_available(){
  if (DTMF_USE_IRQ)
    return DTMF_CODE != NO_DTMF_AVAIL;
  else
    return dtmf_state_changed() > 0;
}

char dtmf_read(){
  if (!DTMF_USE_IRQ) read_dtmf_on_detection();
  char _current = DTMF_CODE;
  DTMF_CODE = NO_DTMF_AVAIL;
  return _current;
}




