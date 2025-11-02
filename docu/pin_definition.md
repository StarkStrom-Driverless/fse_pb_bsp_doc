```c
#define PIN(bank, num) ((((bank) - 'A') << 4) | (num))
```

Based on this makro, a pin id is created

```c
uint16_t led = PIN('C', 1);
```

The Makro PIN creates a unique ID for a pin defined by its port and the pin number.
The result is stored in a 16 bit variable.

--- 

