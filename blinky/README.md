```c
uint16_t led = PIN('C', 1);
```
- [Pin definition according to PIN DEFINITION](../docu/pin_definition.md)

---

```c
static void blinky_task(void *args) {
    uint8_t value = 0;

    for (;;) {
        ss_io_write(led, value);

        value = (value == SS_GPIO_ON) ? SS_GPIO_OFF : SS_GPIO_ON;

        ss_rtos_delay_ms(500);
    }
}
```
- [Task definition according to TASK DEFINITION](../docu/task_definition.md)

- The function `ss_io_write()` takes the the unique pin id and the output value
    - SS_GPIO_OFF - Turn pin off
    - SS_GPIO_ON - Turn pin on
    - SS_GPIO_TOGGLE - Toggle pin state

---

```c
int main(void)
{
    SS_HANDLE_INIT(ss_init());

    SS_HANDLE_INIT(ss_io_init(led, SS_GPIO_MODE_OUTPUT));

    SS_HANDLE_INIT(ss_rtos_task_add(blinky_task, NULL, 1, "blinky_task"));

    ss_rtos_start();

    while (1) {

	}

    return 0;

}
```
- [Main scaliton according to MAIN SCALITON](../docu/main_scaliton.md)
- [Task definition according to TASK DEFINITION](../docu/task_definition.md)

