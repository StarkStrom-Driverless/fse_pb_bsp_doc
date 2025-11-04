The following example shows the buildin timeout detection of the `ss_can` functionality.

```c
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
```

- First of all, the application is receiving CAN messages
- [Reading CAN frames according to CAN READ](../docu/can_read.md)

---

```c
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
```

For checking if a timeout of a CAN message happend, a sperate task is needed.
This Task is needed because the `ss_can_tod_check()` function must be called periodically.
With every call of `ss_can_tod_check()` a CAN-ID specific counter is decremented. 
If the counter reaches the value zero, the `ss_can_tod_check()`functionction returns with,
`SS_FEEDBACK_CAN_TOD_HAPPEND`. 
The ISR restes this counter-value to a user defined value. 
This value in combination with the delay of the `tod_task` can be used to detect timeouts.

---

```c
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
```

- In this example the error led is set in case of a timeout

---

```c
    SS_HANDLE_INIT(ss_can_init(1, 1000000));
    SS_HANDLE_INIT(ss_can_filter_add_msg(1, 0x123));
    SS_HANDLE_INIT(ss_can_tod_add(1, 0x123, 10));
```

For using the `tod` functionality following is required.
- Initialsing the CAN peripharel with `ss_can_init` which tases the peripharel id and the baudrate
- [Using CAN filters according to CAN FILTER](../docu/can_filter.md)
- The function `ss_can_tod_add` addes a CAN ID of the peripharel 1. The reset value is 10,
which means that the example detects a timeout after 5s (10 * 500ms).

