This example shows how to measure frequencies.

```c
uint16_t fm_pin = PIN('A', 5);
```

- [Pin definition according to PIN DEFINITION](../docu/pin_definition.md)

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

- The function `ss_fm_read` provides the frequency of a signal. For this the pin-id is needed.
- In case of very slow frequencies, the function returns zero after 15 fuction-calls, in 
the case, that no raising of falling edge was detected in the intervall.

- [Sending CAN Frames according to CAN_SEND](../docu/can_send.md)

- The frequency-value is transmitted over CAN in this case

---

```c
    SS_HANDLE_INIT(ss_can_init(1, 1000000));

    SS_HANDLE_INIT(ss_fm_init(fm_pin, 1000000));
```

- Init CAN
- With the function `ss_fm_init` the functionality for measuring a frequency of a pin is 
provided. The function takes the pin-id. Be aware, that not every pin and not every 
pin-combination is capable of reading frequencies. The second value is used for setting
the resolution.  In this case, the Resolution is set to 1000000 ticks per seconds which means 1us.