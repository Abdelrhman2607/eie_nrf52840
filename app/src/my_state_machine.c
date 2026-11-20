/*
* @file my_state_machine.c
*/

#include <zephyr/smf.h>
#include <zephyr/sys/printk.h>

#include "LED.h"
#include "BTN.h"
#include "my_state_machine.h"

enum led_state_machine_states{
    LED_STATE_0,
    LED_STATE_1,
    LED_STATE_2,
    LED_STATE_3,
    LED_STATE_4
};

typedef struct {
    struct smf_ctx ctx;
    uint16_t count;
} led_state_object_t;

static const struct smf_state led_states[];
static led_state_object_t led_state_object;


static void led_state_0_entry(void* o){
    printk("entering state 0\n");
    LED_set(LED0, LED_OFF);
    LED_set(LED1, LED_OFF);
    LED_set(LED2, LED_OFF);
    LED_set(LED3, LED_OFF);
}

static void led_state_0_exit(void* o){
    printk("exiting state 0\n");
}

static enum smf_state_result led_state_0_run(void* o){
    if (BTN_check_clear_pressed(BTN0)){
        smf_set_state(SMF_CTX(&led_state_object), &led_states[LED_STATE_1]);
    }

    return SMF_EVENT_HANDLED;
}

static void led_state_1_entry(void* o){
    printk("entering state 1\n");
}

static void led_state_1_exit(void* o){
    printk("exiting state 1\n");
    led_state_object.count = 0;
}

static enum smf_state_result led_state_1_run(void* o){
    if (led_state_object.count >= 250){
        led_state_object.count = 0;
        LED_toggle(LED0);
    }

    else{
        led_state_object.count++;
    }

    if (BTN_check_clear_pressed(BTN3)){
        smf_set_state(SMF_CTX(&led_state_object), &led_states[LED_STATE_0]);
    }

    else if (BTN_check_clear_pressed(BTN2)){
        smf_set_state(SMF_CTX(&led_state_object), &led_states[LED_STATE_4]);
    }

    else if (BTN_check_clear_pressed(BTN1)){
        smf_set_state(SMF_CTX(&led_state_object), &led_states[LED_STATE_2]);
    }


    return SMF_EVENT_HANDLED;
}

static void led_state_2_entry(void* o){
    printk("entering state 2\n");
    LED_set(LED0, LED_ON);
    LED_set(LED2, LED_ON);
    LED_set(LED1, LED_OFF);
    LED_set(LED3, LED_OFF);
}

static void led_state_2_exit(void* o){
    printk("exiting state 2\n");
    led_state_object.count = 0;
}

static enum smf_state_result led_state_2_run(void* o){
    if (led_state_object.count >= 1000){
        led_state_object.count = 0;
        smf_set_state(SMF_CTX(&led_state_object), &led_states[LED_STATE_3]);
    }

    else{
        led_state_object.count++;
    }

    if (BTN_check_clear_pressed(BTN3)){
        smf_set_state(SMF_CTX(&led_state_object), &led_states[LED_STATE_0]);
    }

    return SMF_EVENT_HANDLED;
}

static void led_state_3_entry(void* o){
    printk("entering state 3\n");
    LED_set(LED0, LED_OFF);
    LED_set(LED2, LED_OFF);
    LED_set(LED1, LED_ON);
    LED_set(LED3, LED_ON);
}

static void led_state_3_exit(void* o){
    printk("exiting state 3\n");
    led_state_object.count = 0;
}

static enum smf_state_result led_state_3_run(void* o){
    if (led_state_object.count >= 2000){
        led_state_object.count = 0;
        smf_set_state(SMF_CTX(&led_state_object), &led_states[LED_STATE_2]);
    }

    else{
        led_state_object.count++;
    }

    if (BTN_check_clear_pressed(BTN3)){
        smf_set_state(SMF_CTX(&led_state_object), &led_states[LED_STATE_0]);
    }

    return SMF_EVENT_HANDLED;
}

static void led_state_4_entry(void* o){
    printk("entering state 4\n");
}

static void led_state_4_exit(void* o){
    printk("exiting state 4\n");
    led_state_object.count = 0;
}

static enum smf_state_result led_state_4_run(void* o){
    if (led_state_object.count >= 62){
        led_state_object.count = 0;
        LED_toggle(LED0);
        LED_toggle(LED1);
        LED_toggle(LED2);
        LED_toggle(LED3);
    }

    else{
        led_state_object.count++;
    }

    if (BTN_check_clear_pressed(BTN3)){
        smf_set_state(SMF_CTX(&led_state_object), &led_states[LED_STATE_0]);
    }

    return SMF_EVENT_HANDLED;
}

static const struct smf_state led_states[] = {
    [LED_STATE_0] = SMF_CREATE_STATE(led_state_0_entry, led_state_0_run, led_state_0_exit, NULL, NULL),
    [LED_STATE_1] = SMF_CREATE_STATE(led_state_1_entry, led_state_1_run, led_state_1_exit, NULL, NULL),
    [LED_STATE_2] = SMF_CREATE_STATE(led_state_2_entry, led_state_2_run, led_state_2_exit, NULL, NULL),
    [LED_STATE_3] = SMF_CREATE_STATE(led_state_3_entry, led_state_3_run, led_state_3_exit, NULL, NULL),
    [LED_STATE_4] = SMF_CREATE_STATE(led_state_4_entry, led_state_4_run, led_state_4_exit, NULL, NULL),
};

void state_machine_init(){
    led_state_object.count = 0;
    smf_set_initial(SMF_CTX(&led_state_object), &led_states[LED_STATE_0]);

}

int state_machine_run(){
    return smf_run_state(SMF_CTX(&led_state_object));
}