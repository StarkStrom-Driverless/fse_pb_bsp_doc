This example shows how to use pwm for GPIO's. It is importent to be aware, that not 
every GPIO is capable of this, because this functionlity is only provided by hardware.

```c
uint16_t led = PIN('A', 15);
```

- [Pin definition according to PIN DEFINITION](../docu/pin_definition.md)

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
            }else{
                direction = 0;
            }
        }

        ss_rtos_delay_ms(10);
    }
}
```

- [Task definition according to TASK DEFINITION](../docu/task_definition.md)
- With the function `ss_pwm_write` the pwm-value of a GPIO can be set. The function
needs a value between 0 and 100. There is a `ss_pwm_write_highres` alternvative, which
takes a value between 0 and 1000.
- This example implements a fade from 0 to 100 and viseversa in 10ms steps.

---

```c
    SS_HANDLE_INIT(ss_init());
    SS_HANDLE_INIT(ss_pwm_init(led, 10000));
    SS_HANDLE_INIT(ss_rtos_task_add(pwm_task, NULL, 1, "pwm_task"));
```

- The function `ss_pwm_init` takes the pin-definiton and a frequency value. This is the 
frequency of the pwm-signal. In this case the frequency is 10kHz. 
- [Task definition according to TASK DEFINITION](../docu/task_definition.md)