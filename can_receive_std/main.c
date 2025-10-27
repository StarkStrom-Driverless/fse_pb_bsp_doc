#include "ss.h"

void ss_init_error(SS_FEEDBACK feedback);

uint16_t led = PIN('C', 1);

static void blinky_task(void *args) {
    uint8_t value = 0;

    struct SS_CAN_MSG_QUEUE *queue;
    struct SS_CAN_FRAME msg;

    ss_can_queue_get(1, 0x123, &queue);

    for (;;) {

        if (ss_can_queue_read(queue, &msg) == SS_FEEDBACK_CAN_MSG_RECEIVED) {
            value = (value == SS_GPIO_ON) ? SS_GPIO_OFF : SS_GPIO_ON;
            ss_io_write(led, value);
        }

        ss_rtos_delay_ms(200);
    }
}

int main(void)
{
    SS_HANDLE_INIT(ss_init());

    SS_HANDLE_INIT(ss_io_init(led, SS_GPIO_MODE_OUTPUT));

    SS_HANDLE_INIT(ss_can_init(1, 1000000));
    SS_HANDLE_INIT(ss_can_filter_add_msg(1, 0x123));


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

