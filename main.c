#include <util/delay.h>
#include <avr/power.h>
#include <avr/sleep.h>

#include "ocr_calc.h"
#include "chores.h"
#include "usart.h"
#include "buttons.h"


int main (void) {
  ADCSRA = 0;
  power_adc_disable();

  USART0Init();
  buttons_init();
  tone_init();

  _delay_ms(1000);
  USART0BacklightOff();
  _delay_ms(1000);
  USART0BacklightOff();
  _delay_ms(1000);
  USART0BacklightOff();
  _delay_ms(50);
  int i;
  int last_i = 5;

  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  cli();
  sleep_enable();
  sei();
  sleep_cpu();
  sleep_disable();

  while (1) {

    button_tick(&button_timer);
    button_tick(&button_toggle);

    i = 0;
    if (timer_state() == 0) {
      i += 1;
    }
    if (toggle_state() == 0) {
      i += 2;
    }

    if (i != last_i) {
      last_i = i;
      switch (i) {
        case 0:
          USART0SendString("");
          break;
        case 1:
          USART0SendString("Timer");
          break;
        case 2:
          USART0SendString("\nToggle");
          break;
        case 3:
          USART0SendString("Timer\nToggle");
          break;
      }
    }

    _delay_ms(1);
  }
}

