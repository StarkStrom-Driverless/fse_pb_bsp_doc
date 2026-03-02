#include "ss.h"


void ss_init_error(SS_FEEDBACK feedback);


/* Create a task for receiving can-msgs */
static void rx1_task(void *args) {
    /* initialize a can-frame on the stack */
    struct SS_CAN_FRAME msg;

    /* init a pointer to a can-msg receive queue */
    struct SS_CAN_MSG_QUEUE* queue;

    /* add can-msg receive queue to this task */
    ss_can_queue_add(1, 0x123, &queue);

    for (;;) {

        /* non blocking read on queue. If message is received, it will be copied to msg-var */
        if (ss_can_queue_read(queue, &msg) == SS_FEEDBACK_CAN_MSG_RECEIVED) {
            ss_led_heartbeat_toggle();
        }
        ss_rtos_delay_ms(5000);
    }
}

static void rx2_task(void* args) {
    struct SS_CAN_FRAME msg1;
    struct SS_CAN_FRAME msg2;

    struct SS_CAN_MSG_QUEUE* queue1;
    struct SS_CAN_MSG_QUEUE* queue2;

    ss_can_queue_add(1, 0x123, &queue1);
    ss_can_queue_add(1, 0x124, &queue2);

    for (;;) {
        if (ss_can_queue_read(queue1, &msg1) == SS_FEEDBACK_CAN_MSG_RECEIVED) {
            ss_led_dbg1_toggle();
        }

        if (ss_can_queue_read(queue2, &msg2) == SS_FEEDBACK_CAN_MSG_RECEIVED) {
            ss_led_dbg2_toggle();
        }

        ss_rtos_delay_ms(100);
    }
}

int main(void)
{
    /* Init library */
    SS_HANDLE_INIT(ss_init());

    /* init can1 with 1 mega baud*/
    SS_HANDLE_INIT(ss_can_init(1, 1000000));

    /* add both tasks */
    SS_HANDLE_INIT(ss_rtos_task_add(rx1_task, NULL, 1, "rx1_task"));
    SS_HANDLE_INIT(ss_rtos_task_add(rx2_task, NULL, 1, "rx2_task"));

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

