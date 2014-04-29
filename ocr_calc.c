#include "ocr_calc.h"

int scaler_size[6] = {
  1,
  8,
  64,
  256,
  1024,
  9999
};

int scaler_bits[6] = {
  (1 << CS00),
  (1 << CS01),
  (1 << CS01) | (1 << CS00),
  (1 << CS02),
  (1 << CS02) | (1 << CS00),
  (1 << CS02) | (1 << CS01) | (1 << CS00)
};

void tone_init() {
  DDRD |= (1 << DDD5);

  TCCR0A |= (1 << COM0B1);               // non-inverting
  TCCR0A |= (1 << WGM01) | (1 << WGM00); // fast PWM
}

void notone() {
  TCCR0B &= ~scaler_bits[NO_SCALAR];
}

void tone(int frequency) {
  int scaler_ref = scaler(frequency);
  int ocr = ocr_for_scaler(frequency, scaler_size[scaler_ref]);

  TCCR0B &= ~scaler_bits[NO_SCALAR];
  TCCR0B |= scaler_bits[scaler_ref];

  OCR0B = ocr;
}

int scaler(int frequency) {
  int scaler;
  for (scaler = 0; scaler < sizeof(scaler_size); scaler++) {
    if (scaler_size[scaler] == 0) {
      break;
    }
    if (ocr_for_scaler(frequency, scaler_size[scaler]) < 256) {
      return scaler;
    }
  }

  return scaler; // Best case...
}

int ocr_for_scaler(int frequency, int scaler) {
  return F_CPU / frequency / scaler / 2 - 1;
}

