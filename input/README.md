The following example shows how to read from a GPIO pin.

```c
uint16_t led = PIN('C', 1);
uint16_t button = PIN('C', 11);
```
- [Pin definition according to PIN DEFINITION](../docu/pin_definition.md)

---

```c
    SS_HANDLE_INIT(ss_io_init(led, SS_GPIO_MODE_OUTPUT));

    SS_HANDLE_INIT(ss_io_init(button, SS_GPIO_MODE_INPUT_PU));
```
With the function `ss_io_init` the defined pin is set up as a output with 
`SS_GPIO_MODE_OUTPUT` or as a input. 
The Input can be configured with a PullUp Resistor `SS_GPIO_MODE_INPUT_PU`, with a
PullDown Resistor `SS_GPIO_MODE_INPUT_PD` and without a Resistor `SS_GPIO_MODE_INPUT`.

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
- [Task definition according to TASK DEFINITION](../docu/task_definition.md)

With the function `ss_io_read` the value of the input pin `button` can be read.

