
#include "buttons.h"

ISR (INT0_vect) {
  button_set_state(&button_toggle, PIND & (1 << P_TOGGLE) ? P_HIGH : P_LOW);
}

ISR (INT1_vect) {
  button_set_state(&button_timer, PIND & (1 << P_TIMER) ? P_HIGH : P_LOW);
}

struct Button button_timer = { 0, 10, P_HIGH };
struct Button button_toggle = { 0, 10, P_HIGH };

void buttons_init()
{
  DDRD = 0;
  PORTD |= (1 << P_TOGGLE); // Pull-up toggle switch
  PORTD |= (1 << P_TIMER); // Pull-up timer switch

  EICRA |= (1 << ISC00);    // set INT0 to trigger on ANY logic change
  EIMSK |= (1 << INT0);     // Turns on INT0
  EICRA |= (1 << ISC10);    // set INT1 to trigger on ANY logic change
  EIMSK |= (1 << INT1);     // Turns on INT1
  sei();
}

int timer_state() {
  if (button_get_state(&button_timer) == B_LOW) {
    return 0;
  }

  return 1;
}

int toggle_state() {
  if (button_get_state(&button_toggle) == B_LOW) {
    return 0;
  }

  return 1;
}

void button_tick(struct Button *button)
{
  if (button->ticks <= button->stable_ticks) {
    button->ticks++;
  }
}

void button_set_state(struct Button *button, pin_state new_state) {
  button->ticks = 0;
  button->last_state = new_state;
}

button_state button_get_state(struct Button *button) {
  if (button->ticks < button->stable_ticks) {
    return B_UNSTABLE;
  } else if (button->last_state == P_HIGH) {
    return B_HIGH;
  } else {
    return B_LOW;
  }
}

