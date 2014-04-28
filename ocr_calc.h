
#ifndef OCR_CALC_H
#define OCR_CALC_H

#include <avr/io.h>

#define NO_SCALAR 5

void tone_init();
void tone(int frequency);
void notone();

int scalar(int frequency);
int ocr_for_scalar(int frequency, int scalar);
#endif

