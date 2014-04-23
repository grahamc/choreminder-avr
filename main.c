#include <string.h>
#include <avr/io.h>
#include <util/delay.h>

#include "usart.h"
#include "buttons.h"
#include "chores.h"

#define P_SPEAKER PD5

int main (void) {
  USART0Init();
  buttons_init();



  while (1) {
    if (timer_state()) {
      USART0SendString("timer");
    } else if (toggle_state()) {
      USART0SendString("toggle");
    } else {
      USART0SendString("none\nnone");
    }
    _delay_ms(1000);
  }
}



