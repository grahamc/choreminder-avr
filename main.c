#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>

#include "usart.h"
#include "buttons.h"
#include "chores.h"

#define P_SPEAKER PD5

int chore_pointer = 0;

void write_next_chore()
{
  USART0SendString(tasks[chore_pointer++]);

  if (chore_pointer == sizeof(tasks)) {
    chore_pointer = 0;
  }
}

int main (void) {
  write_next_chore();

  USART0Init();
  _delay_ms(10);
  buttons_init();

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
      }
    } else {
      if (last != 3) {
        last = 3;
        USART0SendString("none\nnone");
      }
    }

    _delay_ms(1);
  }
}



