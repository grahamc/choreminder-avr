
#include "buttons.h"
#include <stdio.h>

void button_tick(struct Button *button)
{
  button->ticks++;
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

void printbutton(struct Button *button) {
  char state;
  button_state bs = button_get_state(button);

  if (bs == B_UNSTABLE) {
    state = 'U';
  } else if (bs == B_HIGH) {
    state = 'H';
  } else {
    state = 'L';
  }


  printf("Ticks: %d\n\tStable: %d\n\tState: %c\n\n",
      button->ticks,
      button->stable_ticks,
      state
  );
}


int main() {
  int i;
  struct Button b1 = { 0, 10, P_HIGH };

  // Make the button stable
  for (i = 0; i < 15; i++) { button_tick(&b1); }
  printbutton(&b1);

  // Unstable: change to LOW
  button_set_state(&b1, P_LOW);
  for (i = 0; i < 5; i++) { button_tick(&b1); } // Not stable
  printbutton(&b1);

  // Make it stable
  for (i = 0; i < 15; i++) { button_tick(&b1); }

  printbutton(&b1);
}

