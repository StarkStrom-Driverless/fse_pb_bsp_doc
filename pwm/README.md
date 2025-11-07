This example demonstrates how to use PWM (Pulse Width Modulation) on GPIO pins. It is important to note that not every GPIO supports PWM, as this functionality depends on hardware capabilities.

```c
uint16_t led = PIN('A', 15);
```

* [Pin definition according to PIN DEFINITION](../docu/pin_definition.md)

---

```c
static void pwm_task(void *args) {
    uint8_t value = 50;
    uint8_t direction = 0;

    for (;;) {
        ss_pwm_write(led, value);

        if (direction == 0) {
            if (value < 100) {
                value++;
            } else {
                direction = 1;
            }
        } else {
            if (value > 0) {
                value--;
            } else {
                direction = 0;
            }
        }

        ss_rtos_delay_ms(10);
    }
}
```

* [Task definition according to TASK DEFINITION](../docu/task_definition.md)
* The function `ss_pwm_write` sets the PWM duty cycle for a GPIO pin. It accepts values between 0 and 100.
* There is also a higher resolution alternative, `ss_pwm_write_highres`, which accepts values from 0 to 1000.
* This example gradually fades the PWM value up and down between 0 and 100 in 10 ms steps.

---

```c
SS_HANDLE_INIT(ss_init());
SS_HANDLE_INIT(ss_pwm_init(led, 10000));
SS_HANDLE_INIT(ss_rtos_task_add(pwm_task, NULL, 1, "pwm_task"));
```

* The function `ss_pwm_init` initializes the PWM functionality for the specified pin with a given frequency—in this case, 10 kHz.
* [Task definition according to TASK DEFINITION](../docu/task_definition.md)
