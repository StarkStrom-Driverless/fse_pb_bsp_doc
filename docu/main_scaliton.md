
```c
#include "ss.h"

void ss_init_error(SS_FEEDBACK feedback);
```

* Include the `ss.h` header, which provides access to all functions of the `fse_pb_bsp` library.
* Declare an error handler function for initialization errors.

---

```c
int main(void)
{
    SS_HANDLE_INIT(ss_init());

    ss_rtos_start();

    while (1) {
        // Main loop does nothing, RTOS tasks are running
    }

    return 0;
}
```

* Call `ss_init()` to initialize the system. This sets up board LEDs, configures the interrupt vector table, and sets clock frequencies to 168 MHz.
* Call `ss_rtos_start()` last during initialization to start the FreeRTOS scheduler.
* The infinite `while(1)` loop runs after RTOS starts but typically remains empty.

---

```c
void ss_init_error(SS_FEEDBACK feedback) {
    uint16_t error = 0xFFFF & feedback;
    uint16_t top_error = (feedback >> 16);

    while(1) {
        ss_led_error_toggle();
        ss_delay(1000);
    }
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char * pcTaskName) {
    while(1) {
        ss_led_error_toggle();
        ss_delay(500);
    }
}
```

* `ss_init_error()` handles errors occurring during system initialization.

  * The `feedback` parameter contains a 32-bit error code where:

    * `top_error` (high 16 bits) identifies the module where the error happened
    * `error` (low 16 bits) describes the specific error
  * In case of an error, the error LED toggles every second.
* `vApplicationStackOverflowHook()` is a FreeRTOS hook function called on stack overflow.

  * It toggles the error LED every 500 ms to indicate a stack overflow.

