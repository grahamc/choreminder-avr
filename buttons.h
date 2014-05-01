#ifndef BUTTONS_H
#define BUTTONS_H

#include <avr/io.h>
#include <avr/interrupt.h>

#define P_TOGGLE PD2
#define P_TIMER  PD3

typedef enum { P_HIGH, P_LOW } pin_state;
typedef enum { B_HIGH, B_LOW, B_UNSTABLE } button_state;

struct Button {
  int ticks;
  int stable_ticks;
  pin_state last_state;
};


void buttons_init();
void button_tick(struct Button *button);
void button_set_state(struct Button *button, pin_state new_state);
button_state button_get_state(struct Button *button);

int timer_state();
struct Button button_timer = { 0, 0, P_HIGH };

int toggle_state();
struct Button button_toggle = { 0, 0, P_HIGH };

#endif
