```c
uint16_t led = PIN('C', 1);
uint16_t adc = PIN('A', 2);
```
- [Pin definition according to PIN DEFINITION](../docu/pin_definition.md)

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

- [Task definition according to TASK DEFINITION](../docu/task_definition.md)
- [Send CAN Frame accoring to CAN SEND](../docu/can_send.md)

- The `ss_adc_read` reads the latest adc-value of the defined `adc` pin id. This function is non-blocking. It dont starts a conversion. The `fse_pb_bsp` library periodically startes adc-convertions in the background. 


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

- [Main scaliton according to MAIN SCALITON](../docu/main_scaliton.md)
- The function `ss_adc_init` initialises the adc for a given pin. In the background for all pins which are initialized with `ss_adc_init`, the library starts a conversion periodically 
- The function `ss_can_init` initializes a can peripheral with a given baudrate
- With the `ss_rtos_task_add` function a task with a given priority is added to FREE-RTOS