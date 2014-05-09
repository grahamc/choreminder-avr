#include "sleep.h"

void save_power() {
  ADCSRA = 0;
  power_adc_disable();
}

void deep_sleep() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  cli();
  sleep_enable();
  sei();
  sleep_cpu();
  sleep_disable();
}

