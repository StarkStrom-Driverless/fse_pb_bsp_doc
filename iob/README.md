This example demonstrates how to use input observation, which means reacting to input events triggered by interrupts rather than polling the input state continuously.

The iob module provides an interface to check for past input changes captured via interrupts.

---

```c
uint16_t input = PIN('C', 11);
```

* [Pin definition according to PIN DEFINITION](../docu/pin_definition.md)

---

```c
static void blinky_task(void *args) {
    uint8_t value = 0;

    for (;;) {
        if (ss_iob_get(input) == 0) {
            ss_led_heartbeat_toggle();
        }
        ss_rtos_delay_ms(5000);
    }
}
```

* [Task definition according to TASK DEFINITION](../docu/task_definition.md)

The function `ss_iob_get()` returns information about whether an input change occurred since the last check.
This allows a slow task to react to input changes without continuous polling, by querying changes after a user-defined delay.
This approach is useful for monitoring input events efficiently.

---

```c
SS_HANDLE_INIT(ss_iob_add(input, SS_GPIO_FALLING));

SS_HANDLE_INIT(ss_rtos_task_add(blinky_task, NULL, 1, "blinky_task"));
```

The function `ss_iob_add` initializes input observation for a pin with a specified trigger behavior.
The pin ID and trigger condition are required; in this case, `SS_GPIO_FALLING` configures the observer to react to falling edges on the input signal.

**Note:** This functionality is hardware-dependent and currently limited to STM32 microcontrollers. For example, you cannot observe both `PIN('A', 0)` and `PIN('B', 0)` separately, since external interrupts for all pins numbered ‘0’ across different ports are multiplexed together.
