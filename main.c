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

  USART0SendString("hey");

  while (1) {
      USART0SendString("timer");
      USART0SendString("toggle");
      USART0SendString("none");

    _delay_ms(1);
  }



  //tone_init();
  tone(4400);
  _delay_ms(200);
  tone(440);
  _delay_ms(200);
  tone(4400);
  _delay_ms(200);
  notone();

  while (1) {
    if (toggle_state()) {
      write_next_chore();
      while (toggle_state()) { _delay_ms(1); } // Wait for it to go down.
      while (!toggle_state()) { _delay_ms(1); } // Wait for ack
      USART0SendString("DONE DONE\nDONE DONE");
      while (toggle_state()) { _delay_ms(1); } // Wait for it to go down.
    }
    _delay_ms(1);
  }
}



