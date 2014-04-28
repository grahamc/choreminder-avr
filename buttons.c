
#include "buttons.h"

void buttons_init()
{
  DDRD = 0;
  PORTD |= (1 << P_TOGGLE); // Pull-up toggle switch
  PORTD |= (1 << P_TIMER); // Pull-up timer switch
}

int timer_state() {
    if (PIND & (1 << P_TIMER)) {
      return 0;
    }

    return 1;
}

int toggle_state() {
    if (PIND & (1 << P_TOGGLE)) {
      return 0;
    }

    return 1;
}

