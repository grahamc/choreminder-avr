#include <avr/io.h>
#include <util/delay.h>

#include "ocr_calc.h"
#include "chores.h"
#include "usart.h"
#include "buttons.h"


int main (void) {
  USART0Init();
  buttons_init();
  tone_init();
  tone(4400);
  _delay_ms(200);
  tone(440);
  _delay_ms(200);
  tone(4400);
  _delay_ms(200);
  notone();

  write_next_chore();

  int last = 0;

  while (1) {
    if (timer_state()) {
      if (last != 1) {
        last = 1;
        write_next_chore();
      }
    } else if (toggle_state()) {
      if (last != 2) {
        last = 2;
        USART0SendString("toggle");
        break;
      }
    } else {
      if (last != 3) {
        last = 3;
        USART0SendString("none\nnone");
      }
    }

    _delay_ms(1);
  }

  while (1) {
      tone(440);
      _delay_ms(1000);
      notone();
      _delay_ms(1000);
  }
}



