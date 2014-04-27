#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>

#include "usart.h"
#include "buttons.h"
#include "chores.h"

#define P_SPEAKER PD5
#define NO_TONE 2048

int scalar(int freq) {
  int max = 255;

  if (freq > max * 256) {
    return 1024;
  } else if (freq > max * 64) {
    return 256;
  } else if (freq > max * 8) {
    return 64;
  } else if (freq > max) { // No prescalar
    return 8;
  } else {
    return 0;
  }
}

int scalar_bits(int scalar) {
  switch (scalar) {
    case NO_TONE:
      return (1 << CS02) | (1 << CS01) | (1 << CS00);
      break;
    case 1024:
      return (1 << CS02) | (1 << CS00);
      break;
    case 256:
      return (1 << CS02);
      break;
    case 64:
      return (1 << CS01) | (1 << CS00);
      break;
    case 8:
      return (1 << CS01);
      break;
    case 0:
    default:
      return 0;
      break;
  }
}

int ocr(int freq) {
  return F_CPU / freq / 2 / scalar(freq);
}

void tone(int freq) {
  OCR0B = ocr(freq);
  TCCR0B &= ~scalar_bits(NO_TONE);
  TCCR0B |= scalar_bits(freq);
}

void pwm(void) {
    DDRD |= (1 << DDD5);
    // PD6 is now an output



    TCCR0A |= (1 << COM0B1);
    // set none-inverting mode

    TCCR0A |= (1 << WGM01) | (1 << WGM00);
    // set fast PWM Mode

    tone(440);
    _delay_ms(1000);
    tone(523);
    _delay_ms(1000);
    tone(783);

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
        USART0SendString("none\nbro");
      }
    }

    _delay_ms(1);
  }
}



