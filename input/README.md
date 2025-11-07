The following example demonstrates how to read from a GPIO pin.

```c
uint16_t led = PIN('C', 1);
uint16_t button = PIN('C', 11);
```

* [Pin definition according to PIN DEFINITION](../docu/pin_definition.md)

---

```c
SS_HANDLE_INIT(ss_io_init(led, SS_GPIO_MODE_OUTPUT));

SS_HANDLE_INIT(ss_io_init(button, SS_GPIO_MODE_INPUT_PU));
```

The `ss_io_init` function configures a pin either as an output with `SS_GPIO_MODE_OUTPUT` or as an input.
Input pins can be configured with:

* Pull-up resistor: `SS_GPIO_MODE_INPUT_PU`
* Pull-down resistor: `SS_GPIO_MODE_INPUT_PD`
* No resistor: `SS_GPIO_MODE_INPUT`

---

```c
static void blinky_task(void *args) {
    uint8_t value = 0;

    for (;;) {
        ss_io_write(led, value);

        value = (value == SS_GPIO_ON) ? SS_GPIO_OFF : SS_GPIO_ON;

        if (ss_io_read(button)) {
            ss_rtos_delay_ms(500);
        } else {
            ss_rtos_delay_ms(100);
        }
    }
}
```

* [Task definition according to TASK DEFINITION](../docu/task_definition.md)

The function `ss_io_read` reads the current value of the input pin `button`.
In this example, the blinking speed of the LED depends on whether the button is pressed or not.
