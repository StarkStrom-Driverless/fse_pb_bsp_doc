The following example shows how to use ID specific message queues.

---

```c
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

        ss_rtos_delay_ms(100);
    }
}
```

- [Reading CAN frames according to CAN READ](../docu/can_read.md)
- `can_queue_task` is a task with a separate message queue
- `slow_can_task` is a task whichs message queue contains all left can messages

---

```c

    SS_HANDLE_INIT(ss_can_init(1, 1000000));
    SS_HANDLE_INIT(ss_can_filter_add_msg(1, 0x123));
    SS_HANDLE_INIT(ss_can_filter_add_msg(1, 0x124));
    SS_HANDLE_INIT(ss_can_queue_handle_add(1, 0x123, can_queue_task, NULL, 2));

    SS_HANDLE_INIT(ss_rtos_task_add(slow_can_task, NULL, 4, "slow_can_task"));
```

[Using CAN filters according to CAN FILTER](../docu/can_filter.md).

Initialsing a can_queue_handle with `ss_rtos_task_add`. This function directly creates a
free RTOS task for a specific can message id. The function needs the CAN peripharel id, 
The message id, a pointer to a FREE RTOS Task, a pointer to a user defined struct and 
a prio for the can-reading task

---

![alt text](img/can_receive_queue.drawio.png)

This picture demonstrates, the functionality of this concept. All incoming CAN messages,
are passing the interrupt service routine. This routine than copies the incomming messages,
to the seperate message queues, which are consumed by the tasks. 
This concept enables to seperate fast messages from slow messages and prevent complexity 
because, reading a message only has complexity O(1). Moreover, no global can_receive task
is needed.