#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include "usart.h"
#include "buttons.h"

#define P_SPEAKER PD5

int main (void) {
  USART0Init();
  buttons_init();



  while (1) {
    if (timer_state()) {
      USART0SendByte(0xFE);
      USART0SendByte(128);
      USART0SendString("timer");
    } else if (toggle_state()) {
      USART0SendByte(0xFE);
      USART0SendByte(192);
      USART0SendString("toggle");
    } else {
      USART0SendByte(0xFE);
      USART0SendByte(128);
      USART0SendString("none  ");
    }
    _delay_ms(10);
  }
}



