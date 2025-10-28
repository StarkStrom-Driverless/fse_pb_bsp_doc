#include "ss.h"

void ss_init_error(SS_FEEDBACK feedback);




static void can_queue_task(void *args) {
    struct SS_CAN_FRAME msg;
    struct SS_CAN_MSG_QUEUE* queue;

    ss_can_queue_get(1, 0x123, &queue);

    for (;;) {
        if (ss_can_queue_read(queue, &msg) == SS_FEEDBACK_CAN_MSG_RECEIVED) {
            ss_led_heartbeat_toggle();
        }

        ss_rtos_delay_ms(10);
    }
}

static void slow_can_task(void *args) {
    struct SS_CAN_FRAME msg;
    struct SS_CAN_MSG_QUEUE* queue;

    ss_can_queue_get(1, 0x124, &queue);

    for (;;) {
        if (ss_can_queue_read(queue, &msg) == SS_FEEDBACK_CAN_MSG_RECEIVED) {
            ss_led_dbg1_toggle();
        }

        ss_rtos_delay_ms(10);
    }
}

int main(void)
{
    SS_HANDLE_INIT(ss_init());

    SS_HANDLE_INIT(ss_can_init(1, 1000000));
    SS_HANDLE_INIT(ss_can_filter_add_msg(1, 0x123));
    SS_HANDLE_INIT(ss_can_filter_add_msg(1, 0x124));
    SS_HANDLE_INIT(ss_can_queue_handle_add(1, 0x123, can_queue_task, NULL, 2));

    SS_HANDLE_INIT(ss_rtos_task_add(slow_can_task, NULL, 4, "slow_can_task"));

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

