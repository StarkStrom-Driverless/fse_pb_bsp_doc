#include "ss.h"

void ss_init_error(SS_FEEDBACK feedback);


uint16_t input = PIN('C', 11);

static void blinky_task(void *args) {
    uint8_t value = 0;

    for (;;) {
        if (ss_iob_get(input) == 0) {
            ss_led_heartbeat_toggle();
        }
        ss_rtos_delay_ms(5000);
    }
}

int main(void)
{
    SS_HANDLE_INIT(ss_init());

    SS_HANDLE_INIT(ss_iob_add(input, SS_GPIO_FALLING));

    SS_HANDLE_INIT(ss_rtos_task_add(blinky_task, NULL, 1, "blinky_task"));

    ss_rtos_start();

    while (1) {

	}

    return 0;

}

void ss_init_error(SS_FEEDBACK feedback) {
    uint16_t error = 0xFFFF & feedback;
    uint16_t top_error = (feedback >> 16);
    while(1) {
        ss_led_error_toggle();
        ss_delay(1000);
    }
}


void vApplicationStackOverflowHook(TaskHandle_t xTask, char * pcTaskName) {
    while(1) {
        ss_led_error_toggle();
        ss_delay(500);
    }
}

