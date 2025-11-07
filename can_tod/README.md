The following example demonstrates the built-in timeout detection feature of the `ss_can` module.

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

* This task receives CAN messages continuously.
* [Reading CAN frames according to CAN READ](../docu/can_read.md)

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

To detect CAN message timeouts, a separate task is required to call `ss_can_tod_check()` periodically.
Each call to `ss_can_tod_check()` decrements a CAN-ID-specific counter.
If this counter reaches zero, the function returns `SS_FEEDBACK_CAN_TOD_HAPPEND` indicating a timeout occurred.

The interrupt service routine (ISR) resets this counter to a user-defined value whenever a message is received.
The timeout duration depends on this reset value combined with the delay between calls to `ss_can_tod_check()`.

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

* In this example, the error LED toggles if a timeout is detected.

---

```c
SS_HANDLE_INIT(ss_can_init(1, 1000000));
SS_HANDLE_INIT(ss_can_filter_add_msg(1, 0x123));
SS_HANDLE_INIT(ss_can_tod_add(1, 0x123, 10));
```

To use the timeout detection (`tod`) functionality, the following steps are required:

* Initialize the CAN peripheral with `ss_can_init()`, providing the peripheral ID and baud rate.
* [Using CAN filters according to CAN FILTER](../docu/can_filter.md)
* Add the CAN ID to the timeout detection system with `ss_can_tod_add()`. The reset value `10` means a timeout is detected after approximately 5 seconds (10 × 500 ms delay in `tod_task`).