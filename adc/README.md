# ADC

```c
uint16_t led = PIN('C', 1);
uint16_t adc = PIN('A', 2);
```
- Defining pin ids 

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

- The `blinky_task` function is the FREE-RTOS Function. It contains a `for(;;)` endlos loop, which is delayed with the `ss_rtos_delay_ms` function.
- If the `ss_rtos_delay_ms` is called, all stack-variables `value`, `msg` and `rc`are safed.
- The `ss_can_frame_set_common` function sets the fields of a frame like id and dlc
- The `ss_adc_read` reads the latest adc-value of the defined `adc` pin id. This function is non-blocking. It dont starts a conversion. The `fse_pb_bsp` library periodically startes adc-convertions in the background. 
- The function `ss_can_frame_set_signal` writes a value to a specific interval in the can-message
- With the `ss_can_send` function a can-message is send


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

- The function `ss_adc_init` initialises the adc for a given pin. In the background for all pins which are initialized with `ss_adc_init`, the library starts a conversion periodically 
- The function `ss_can_init` initializes a can peripheral with a given baudrate
- With the `ss_rtos_task_add` function a task with a given priority is added to FREE-RTOS