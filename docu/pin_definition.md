
```c
#define PIN(bank, num) ((((bank) - 'A') << 4) | (num))
```

* This macro creates a unique 8-bit ID for a GPIO pin based on its port letter (`bank`) and pin number (`num`).
* It works by converting the port letter into a number (e.g., `'A'` → 0, `'B'` → 1, etc.) by subtracting `'A'`.
* This number is then shifted left by 4 bits (multiplying by 16), reserving the upper nibble for the port.
* The pin number (`num`) occupies the lower 4 bits.
* Resulting in a single byte where the high nibble is the port and the low nibble is the pin number.

Example:

```c
uint16_t led = PIN('C', 1);
```

* For port `'C'` (which is `'C' - 'A' = 2`), shifted left by 4 → `0x20`
* Pin number `1` → `0x01`
* Combined ID → `0x21`

This ID uniquely identifies port C pin 1 in a compact form.
