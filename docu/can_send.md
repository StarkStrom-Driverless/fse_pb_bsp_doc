```c
struct SS_CAN_FRAME msg;

ss_can_frame_set_common(&msg, 0x123, 2);
ss_can_frame_set_signal(&msg, 15, 1, 0x12);

ss_can_send(1, &msg);
```

- The `ss_can_frame_set_common` function sets the fields of a frame like id and dlc
- The function `ss_can_frame_set_signal` writes a value to a specific interval in the can-message
- With the `ss_can_send` function a can-message is send