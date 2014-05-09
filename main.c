#include <util/delay.h>

#include "buttons.h"
#include "chores.h"
#include "ocr_calc.h"
#include "sleep.h"
#include "usart.h"

#define TIMER_LENGTH 300

#define STATE_GO_OFF 0
#define STATE_IS_OFF 1
#define STATE_HAS_CHORE 2

void tick()
{
  button_tick(&button_timer);
  button_tick(&button_toggle);
  _delay_ms(1);
}

int main (void) {
  save_power();
  USART0Init();
  buttons_init();
  tone_init();


  int useless_steps = 0;
  int state = STATE_GO_OFF;

  while (1) {
    if (useless_steps >= 1000) {
      useless_steps = 0;
      state = STATE_GO_OFF;
    }

    if (state == STATE_GO_OFF) {
      state = STATE_IS_OFF;

      USART0SendString("");
      USART0BacklightOff();
      deep_sleep();
    }

    tick();

    if (toggle_state() == 0) {
      useless_steps = 0;

      USART0BacklightOn();
      write_next_chore();
      while (toggle_state() == 0) { tick(); } // Wait for button to be released

      int seconds = 0;
      int miliseconds = 0;

      while (1) {
        if (toggle_state() == 0) { state = STATE_GO_OFF; notone(); break; }
        if (timer_state() == 0) { miliseconds = 0; seconds = 0; notone(); }

        miliseconds++;
        if (miliseconds >= 1000) {
          seconds++;
          miliseconds = 0;
        }

        if (seconds == TIMER_LENGTH) {
          tone(4400);
        } else if (seconds > 1000) {
          seconds = (TIMER_LENGTH + 1);
        }

        tick();
      }
    } else {
      useless_steps++;
    }
  }
}



