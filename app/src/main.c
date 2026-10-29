/**
 * @file main.c
 */

#include <inttypes.h>

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#include "BTN.h"
#include "LED.h"

#define SLEEP_MS 100

int main(void) {
  if (0 > BTN_init()) {
    return 0;
  }
  if (0 > LED_init()) {
    return 0;
  }

  while (1) {
    // LED_toggle(LED0);
    // k_msleep(SLEEP_MS);
    // LED_toggle(LED1);
    // k_msleep(SLEEP_MS);
    // LED_toggle(LED2);
    // k_msleep(SLEEP_MS);
    // LED_toggle(LED3);
    // k_msleep(SLEEP_MS);
  }
  return 0;
}
