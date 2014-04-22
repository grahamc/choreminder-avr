#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include "usart.h"

#define P_TOGGLE PD2
#define P_TIMER  PD3
#define P_SPEAKER PD5



int timer_state() {
    if (PIND & (1 << P_TIMER)) {
      return 0;
    }

    return 1;
}

int toggle_state() {
    if (PIND & (1 << P_TOGGLE)) {
      return 0;
    }

    return 1;
}

void USART0SendString(char* str) {
  // Clean screen
  USART0SendByte(0xFE);
  USART0SendByte(0x01);

  // Display data
  int i;
  for (i = 0; i < strlen(str); i++) {
    USART0SendByte(str[i]);
  }
}

int main (void) {
  USART0Init();

  DDRD = 0;
  PORTD |= (1 << P_TOGGLE); // Pull-up toggle switch
  PORTD |= (1 << P_TIMER); // Pull-up timer switch

  while(1) {
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



