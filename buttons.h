#ifndef BUTTONS_H
#define BUTTONS_H
#include <avr/io.h>

#define P_TOGGLE PD2
#define P_TIMER  PD3

void buttons_init();
int timer_state();
int toggle_state();
#endif
