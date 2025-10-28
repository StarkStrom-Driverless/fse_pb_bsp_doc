#include "ss.h"

void ss_init_error(SS_FEEDBACK feedback);

uint16_t fm_pin = PIN('A', 0);

static void fm_task(void *args) {
    float value;
    struct SS_CAN_FRAME msg;
    for (;;) {
        ss_fm_read(fm_pin, &value);

        ss_can_frame_set_common(&msg, 0x123, 4);
        ss_can_frame_set_signal(&msg, 0, 32, (uint32_t)value);
        ss_can_send(1, &msg);

        ss_rtos_delay_ms(500);
    }
}

int main(void)
{
    SS_HANDLE_INIT(ss_init());

    SS_HANDLE_INIT(ss_can_init(1, 1000000));

    SS_HANDLE_INIT(ss_fm_init(fm_pin, 1000));

    SS_HANDLE_INIT(ss_rtos_task_add(fm_task, NULL, 1, "fm_task"));

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

