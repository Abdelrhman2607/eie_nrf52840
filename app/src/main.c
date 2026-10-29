/**
 * @file main.c
 */

#include <inttypes.h>

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#include "BTN.h"
#include "LED.h"

#define SLEEP_MS 100
#define STEP_DELAY_MS 100

int main(void) {
  if (0 > BTN_init()) {
    return 0;
  }
  if (0 > LED_init()) {
    return 0;
  }

  uint8_t counter = 0b0000;

  while (counter < 16) {
    if (BTN_check_clear_pressed(BTN0)){
      if (counter == 0){
        printk("--- START ---\r\n");
      }
      printk("Counter: %d\r\n", counter);

      if (counter & 1){
        LED_set(LED0, LED_ON);
      }
      else{
        LED_set(LED0, LED_OFF);
      }

      if (counter & 2){
        LED_set(LED1, LED_ON);
      }
      else{
        LED_set(LED1, LED_OFF);
      }

      if (counter & 4){
        LED_set(LED2, LED_ON);
      }
      else{
        LED_set(LED2, LED_OFF);
      }

      if (counter & 8){
        LED_set(LED3, LED_ON);
      }
      else{
        LED_set(LED3, LED_OFF);
      }
      counter = counter == 15 ? 0 : counter + 1;
    }
    k_msleep(SLEEP_MS);
  }
  return 0;
}
