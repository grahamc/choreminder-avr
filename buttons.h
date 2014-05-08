#ifndef BUTTONS_H
#define BUTTONS_H

#include <avr/io.h>
#include <avr/interrupt.h>

#define P_TOGGLE PD2
#define P_TIMER  PD3

extern struct Button button_timer;
extern struct Button button_toggle;

typedef enum { P_HIGH, P_LOW } pin_state;
typedef enum { B_HIGH, B_LOW, B_UNSTABLE } button_state;

struct Button {
  volatile int ticks;
  volatile int stable_ticks;
  volatile pin_state last_state;
};


void buttons_init();
void button_tick(struct Button *button);
void button_set_state(struct Button *button, pin_state new_state);
button_state button_get_state(struct Button *button);

int timer_state();

int toggle_state();

#endif
