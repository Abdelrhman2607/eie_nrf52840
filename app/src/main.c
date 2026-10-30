/*
* main.c
*/

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define SLEEP_MS 500

int main(void){
    static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
    static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);

    if (!(gpio_is_ready_dt(&led0) && gpio_is_ready_dt(&led1))){
            return -1;
        }

    int ret0 = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);
    int ret1 = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_INACTIVE);
    if (ret0 < 0 || ret1 < 0){
        return ret0;
    }

    int speed_toggle = 0;
    while(1){
        
        gpio_pin_toggle_dt(&led0);
        if (speed_toggle) // LED1 toggles every 2 SLEEP_MS delays
            gpio_pin_toggle_dt(&led1);

        k_msleep(SLEEP_MS);
        speed_toggle = !speed_toggle;
    }

    return 0;
}