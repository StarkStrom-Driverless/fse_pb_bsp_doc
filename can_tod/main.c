#include "ss.h"

void ss_init_error(SS_FEEDBACK feedback);

uint8_t timeout_detected = 0;

static void can_task(void *args) {
    struct SS_CAN_MSG_QUEUE *queue;
    struct SS_CAN_FRAME msg;

    ss_can_queue_get(1, 0x123, &queue);

    for (;;) {

        if (ss_can_queue_read(queue, &msg) == SS_FEEDBACK_CAN_MSG_RECEIVED) {
            ss_led_heartbeat_toggle();

            ss_can_tod_update(1, 0x123);
        }

        ss_rtos_delay_ms(200);
    }
}

static void state_task(void *args) {

    for (;;) {

        if (timeout_detected == 1) {
            ss_led_error_toggle();
        } else {
            ss_led_error_off();
        }

        ss_rtos_delay_ms(200);
    }
}

static void tod_task(void *args) {

    for (;;) {

        if (ss_can_tod_check() == SS_FEEDBACK_CAN_TOD_HAPPEND) {
            timeout_detected = 1;
        } else {
            timeout_detected = 0;
        }

        ss_rtos_delay_ms(500);
    }
}


int main(void)
{
    SS_HANDLE_INIT(ss_init());


    SS_HANDLE_INIT(ss_can_init(1, 1000000));
    SS_HANDLE_INIT(ss_can_filter_add_msg(1, 0x123));
    SS_HANDLE_INIT(ss_can_tod_add(1, 0x123, 10));


    SS_HANDLE_INIT(ss_rtos_task_add(can_task, NULL, 1, "can_task"));
    SS_HANDLE_INIT(ss_rtos_task_add(state_task, NULL, 4, "state_task"));
    SS_HANDLE_INIT(ss_rtos_task_add(tod_task, NULL, 1, "tod_task"));

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

