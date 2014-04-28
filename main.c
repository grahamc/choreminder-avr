#include <avr/io.h>
#include <util/delay.h>
#include "ocr_calc.h"

int main (void) {
  tone_init();

  int i;
  while (1) {
    for (i = 0; i <= 4400; i += 440) {
      tone(i);
      _delay_ms(1000);
    }
  }
}



