#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "ocr_calc.h"
#include "chores.h"
#include "usart.h"
#include "buttons.h"

volatile int button_toggle_stability = 0;
volatile int button_toggle_state = 0;

volatile int button_timer_stability = 0;
volatile int button_timer_state = 0;

ISR (INT0_vect) {
  button_toggle_stability = 0;
  if (PIND & (1 << P_TOGGLE)) {
    button_toggle_state = 0;
  } else {
    button_toggle_state = 1;
  }
}

ISR (INT1_vect) {
  button_timer_stability = 0;
  if (PIND & (1 << P_TIMER)) {
    button_timer_state = 0;
  } else {
    button_timer_state = 1;
  }
}


int main (void) {
  USART0Init();
  buttons_init();
  tone_init();

  EICRA |= (1 << ISC00);    // set INT0 to trigger on ANY logic change
  EIMSK |= (1 << INT0);     // Turns on INT0
  EICRA |= (1 << ISC01);    // set INT0 to trigger on ANY logic change
  EIMSK |= (1 << INT1);     // Turns on INT0
  sei();

  USART0SendString("hey");

  while (1) {
    if (button_timer_stability < 10) {
      button_timer_stability++;
    }

    if (button_toggle_stability < 10) {
      button_toggle_stability++;
    }

    if (button_timer_stability == 10 && button_timer_state == 0) {
      USART0SendString("timer");
    }
    if (button_toggle_stability == 10 && button_toggle_state == 0) {
      USART0SendString("toggle");
    }

    if (button_toggle_stability < 10 && button_timer_stability < 10) {
      USART0SendString("none");
    }

    if (button_toggle_stability == 10) {
      button_toggle_stability++;
    }

    if (button_timer_stability == 10) {
      button_timer_stability++;
    }

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



