#include <avr/io.h>
#include <util/delay.h>
#include "ocr_calc.h"

int main (void) {
  tone_init();

  while (1) {
      tone(440);
      _delay_ms(1000);
      notone();
      _delay_ms(1000);
  }
}



