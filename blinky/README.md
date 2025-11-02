# Blinky

```c
uint16_t led = PIN('C', 1);
```
- Defining a unique id for a pin by its port name `c` and the pin number `1`

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



