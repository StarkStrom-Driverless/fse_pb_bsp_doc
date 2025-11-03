The following example shows how to receive CAN-Messages

---

```c
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
```

- [Reading CAN frames according to CAN READ](../docu/can_read.md)

---


```c
    SS_HANDLE_INIT(ss_io_init(led, SS_GPIO_MODE_OUTPUT));

    SS_HANDLE_INIT(ss_can_init(1, 1000000));
    SS_HANDLE_INIT(ss_can_filter_add_msg(1, 0x123));


    SS_HANDLE_INIT(ss_rtos_task_add(blinky_task, NULL, 1, "blinky_task"));
```

- [Using CAN filters according to CAN FILTER](../docu/can_filter.md)

