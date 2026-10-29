/**
 * @file main.c
 */

#include <inttypes.h>

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#include "BTN.h"
#include "LED.h"

#define STEP_DELAY_MS 100

int main(void) {
  if (0 > BTN_init()) {
    return 0;
  }
  if (0 > LED_init()) {
    return 0;
  }

  while (1) {
    for (uint8_t duty_cycle = 0; duty_cycle <= 100; duty_cycle += 10){
      LED_pwm(LED0, duty_cycle);
      k_msleep(STEP_DELAY_MS);
    }
  }
  return 0;
}
