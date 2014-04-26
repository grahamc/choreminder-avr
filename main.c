#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>

#include "usart.h"
#include "buttons.h"
#include "chores.h"

#define P_SPEAKER PD5

void pwm(void) {
    DDRD |= (1 << DDD5);
    // PD6 is now an output

    OCR0B = 128;
    // set PWM for 50% duty cycle


    TCCR0B |= (1 << COM0B1);
    // set none-inverting mode

    TCCR0B |= (1 << WGM01) | (1 << WGM00);
    // set fast PWM Mode

    TCCR0B |= (1 << CS01);
    // set prescaler to 8 and starts PWM


    while (1);
    {
        // we have a working Fast PWM
    }

}

int main (void) {
pwm();
  USART0Init();
  buttons_init();


  int last = 0;

  while (1) {
    if (timer_state()) {
      if (last != 1) {
        last = 1;
        USART0SendString("timer");
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



