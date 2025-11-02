```c
#include "ss.h"

void ss_init_error(SS_FEEDBACK feedback);
```
- Include the `ss.h` header file. This file provides access to all functions of fse_pb_bsp
- Define a error handler function for initialization

---

```c
int main(void)
{
    SS_HANDLE_INIT(ss_init());

    ss_rtos_start();

    while (1) {

	}

    return 0;

}
```
- The first required thing is to call the `ss_init()` function. This will init the board-leds, set the interrupt vector table register and initializes clock-frequencies to 168Mhz.
- The last function to call in the initialization process is the `ss_rtos_start()` function. This will start the FREE-RTOS scheduler.

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
- The `ss_init_error` function is a handler function for errors during the initialization process. It takes a `SS_FEEDBACK` error-code which contains a top_error which is mostly a error-code which describes in which module the error happend and a normal error which describes what kind of error happend.
- The `vApplicationStackOverflowHook` function is a handler function fo stack-overflows in FREE-RTOS