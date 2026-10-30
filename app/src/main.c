/*
* main.c
*/

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

int main(void){
    static const struct gpio_dt_spec led0 = GPIO_SPEC_GET(LED0_NODE, gpios);

    if (!gpio_is_ready_dt(&led0)){
            return -1;
        }

    int ret = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE)
    if (ret < 0){
        return ret;
    }

    while(1){
        
    }

    return 0;
}