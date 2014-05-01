#ifndef BUTTONS_H
#define BUTTONS_H

typedef enum { P_HIGH, P_LOW } pin_state;
typedef enum { B_HIGH, B_LOW, B_UNSTABLE } button_state;

struct Button {
  int ticks;
  int stable_ticks;
  pin_state last_state;
};


void buttons_init();
int timer_state();
int toggle_state();

void button_tick(struct Button *button);
void button_set_state(struct Button *button, pin_state new_state);
button_state button_get_state(struct Button *button);

#endif
