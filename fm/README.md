This example demonstrates how to measure signal frequencies.

```c
uint16_t fm_pin = PIN('A', 5);
```

* [Pin definition according to PIN DEFINITION](../docu/pin_definition.md)

---

```c
static void fm_task(void *args) {
    float value;
    struct SS_CAN_FRAME msg;

    for (;;) {
        ss_fm_read(fm_pin, &value);

        ss_can_frame_set_common(&msg, 0x123, 4);
        ss_can_frame_set_signal(&msg, 0, 32, (uint32_t)value);
        ss_can_send(1, &msg);

        ss_rtos_delay_ms(10);
    }
}
```

* The function `ss_fm_read` measures the frequency of a signal on the specified pin ID.

* If no rising or falling edge is detected within 15 consecutive calls, typically indicating very low frequency signals, the function returns zero.

* The measured frequency value is transmitted over CAN in this example.

* [Sending CAN Frames according to CAN_SEND](../docu/can_send.md)

---

```c
SS_HANDLE_INIT(ss_can_init(1, 1000000));

SS_HANDLE_INIT(ss_fm_init(fm_pin, 1000000));
```

* Initializes the CAN peripheral.
* The function `ss_fm_init` enables frequency measurement on the specified pin.
* Note that not all pins or pin combinations support frequency measurement.
* The second parameter sets the measurement resolution, defined here as 1,000,000 ticks per second (i.e., 1 microsecond resolution).
