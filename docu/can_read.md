```c
    struct SS_CAN_FRAME msg;
    struct SS_CAN_MSG_QUEUE* queue;

    ss_can_queue_get(1, 0x123, &queue);

    for (;;) {
        if (ss_can_queue_read(queue, &msg) == SS_FEEDBACK_CAN_MSG_RECEIVED) {
            // do-something
        }

        ss_rtos_delay_ms(10);
    }
```

For reading a specific CAN-Message from a queue, it is required to create a local or global
`SS_CAN_FRAME` message and a pointer to a `SS_CAN_MSG_QUEUE`. 
Befor reading a CAN-Frame from a queue, it is required to init the msg queue pointer to 
a id specifc queue with the function `ss_can_queue_get()`.
This function needs the device name, the CAN message id and the address of the msg queue pointer.
After this, it can be periodically checked if a can-message received with the `ss_can_queue_read` function. For this, the function needs the queue pointer and the 
address of the local can frame. The function returns `SS_FEEDBACK_CAN_MSG_RECEIVED` if 
a message was poped from the queue. In this case, the content of the message is copied to
the local message frame.

For the case, that the task is not a id specific task-handle, all not directly to a 
can_queue_handle related messages are combined to a single queue, which can be read with the same functionality.