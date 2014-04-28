#include "ocr_calc.h"

int scalar_size[6] = {
  1,
  8,
  64,
  256,
  1024,
  9999
};

int scalar_bits[6] = {
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
  TCCR0B &= ~scalar_bits[NO_SCALAR];
}

void tone(int frequency) {
  int scalar_ref = scalar(frequency);
  int ocr = ocr_for_scalar(frequency, scalar_size[scalar_ref]);

  TCCR0B &= ~scalar_bits[NO_SCALAR];
  TCCR0B |= scalar_bits[scalar_ref];

  OCR0B = ocr;
}

int scalar(int frequency) {
  int scalar;
  for (scalar = 0; scalar < sizeof(scalar_size); scalar++) {
    if (scalar_size[scalar] == 0) {
      break;
    }
    if (ocr_for_scalar(frequency, scalar_size[scalar]) < 256) {
      return scalar;
    }
  }

  return scalar; // Best case...
}

int ocr_for_scalar(int frequency, int scalar) {
  return F_CPU / frequency / scalar / 2 - 1;
}

