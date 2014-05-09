#ifndef SLEEP_H
#define SLEEP_H

#include <avr/interrupt.h>
#include <avr/power.h>
#include <avr/sleep.h>

void save_power();
void deep_sleep();

#endif

