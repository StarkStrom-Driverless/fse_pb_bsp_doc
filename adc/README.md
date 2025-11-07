```c
uint16_t led = PIN('C', 1);
uint16_t adc = PIN('A', 2);
```

* [Pin definition according to PIN DEFINITION](../docu/pin_definition.md)

---

```c
static void blinky_task(void *args) {
    uint16_t value = 0;
    struct SS_CAN_FRAME msg;
    SS_FEEDBACK rc;
    for (;;) {
        ss_can_frame_set_common(&msg, 0x123, 2);

        rc = ss_adc_read(adc, &value);

        if (rc != SS_FEEDBACK_OK) {
            ss_can_frame_set_signal(&msg, 15, 1, 1);
        } else {
            ss_can_frame_set_signal(&msg, 0, 16, value);
        }

        ss_can_send(1, &msg);

        ss_rtos_delay_ms(500);
    }
}
```

* [Task definition according to TASK DEFINITION](../docu/task_definition.md)
* [Send CAN Frame accoring to CAN SEND](../docu/can_send.md)

The function `ss_adc_read` retrieves the latest ADC value from the defined `adc` pin.
It operates **non-blocking** and does **not** start a conversion itself.
The `fse_pb_bsp` library periodically triggers ADC conversions in the background.

---

```c
int main(void)
{
    SS_HANDLE_INIT(ss_init());

    SS_HANDLE_INIT(ss_adc_init(adc));

    SS_HANDLE_INIT(ss_can_init(1, 1000000));

    SS_HANDLE_INIT(ss_rtos_task_add(blinky_task, NULL, 1, "blinky_task"));

    ss_rtos_start();

    while (1) {

	}

    return 0;

}
```

* [Main scaliton according to MAIN SCALITON](../docu/main_scaliton.md)

The function `ss_adc_init` initializes the ADC for the specified pin.
For all pins initialized in this way, the library automatically performs periodic conversions in the background.

The function `ss_can_init` initializes a CAN interface with the given baud rate.

Using `ss_rtos_task_add`, a task is created and added to **FreeRTOS** with the specified priority.
