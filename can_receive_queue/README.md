The following example demonstrates how to use **ID-specific CAN message queues**.

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

* [Reading CAN frames according to CAN READ](../docu/can_read.md)
* `can_queue_task` is a task with its own dedicated message queue
* `slow_can_task` is a task whose message queue receives all remaining CAN messages

---

```c
SS_HANDLE_INIT(ss_can_init(1, 1000000));
SS_HANDLE_INIT(ss_can_filter_add_msg(1, 0x123));
SS_HANDLE_INIT(ss_can_filter_add_msg(1, 0x124));
SS_HANDLE_INIT(ss_can_queue_handle_add(1, 0x123, can_queue_task, NULL, 2));

SS_HANDLE_INIT(ss_rtos_task_add(slow_can_task, NULL, 4, "slow_can_task"));
```

* [Using CAN filters according to CAN FILTER](../docu/can_filter.md)

The example initializes a **CAN message queue handle** using `ss_can_queue_handle_add()`.
This function automatically creates a **FreeRTOS task** bound to a specific CAN message ID.
Its parameters include:

* The CAN peripheral ID
* The CAN message ID
* A pointer to the FreeRTOS task function
* A pointer to an optional user-defined structure
* The task priority for message handling

---

![alt text](img/can_receive_queue.drawio.png)

This diagram illustrates the concept.
All incoming CAN messages pass through the **interrupt service routine (ISR)**, which copies each message into its corresponding **message queue**.
These queues are then processed independently by their respective tasks.

This design allows **fast** and **slow** message handling to be separated efficiently, achieving constant-time complexity **O(1)** for reading a message.
Furthermore, it eliminates the need for a global CAN receive task, resulting in cleaner and more scalable system architecture.
