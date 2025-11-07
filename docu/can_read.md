
```c
struct SS_CAN_FRAME msg;
struct SS_CAN_MSG_QUEUE* queue;

ss_can_queue_get(1, 0x123, &queue);

for (;;) {
    if (ss_can_queue_read(queue, &msg) == SS_FEEDBACK_CAN_MSG_RECEIVED) {
        // do something
    }

    ss_rtos_delay_ms(10);
}
```

To read a specific CAN message from a queue, you need to create a local or global `SS_CAN_FRAME` variable and a pointer to an `SS_CAN_MSG_QUEUE`.

Before reading a CAN frame from the queue, the queue pointer must be initialized to an ID-specific queue using the function `ss_can_queue_get()`.
This function requires the CAN peripheral ID, the CAN message ID, and the address of the queue pointer.

After initialization, you can periodically check for received messages using `ss_can_queue_read()`.
This function takes the queue pointer and the address of your local CAN frame.
If a message is available, it returns `SS_FEEDBACK_CAN_MSG_RECEIVED` and copies the message content into the local frame.

If the task is not associated with an ID-specific queue handle, all messages not tied to a specific queue are combined into a single queue. This queue can be read using the same approach.
