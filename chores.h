
#ifndef CHORES_H
#define CHORES_H

#include <avr/eeprom.h>
#include "usart.h"

#define CHORE_COUNT 35

void write_next_chore();
uint8_t get_chore_location();
void set_chore_location(uint8_t i);
#endif

