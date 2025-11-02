# Usage

## Creating a new example
```shell
# Creating a folder
mkdir example_example
cd example_example

# adding lib
git submodule add git@github.com:StarkStrom-Driverless/fse_pb_bsp.git

# installing 
cd fse_pb_bsp
./init.sh

# go back
cd ..

```

## Preparing a existing example
```shell
# goto example dir
cd example_example

# update submodule 
git submodule update

# installing 
cd fse_pb_bsp
./init.sh

# go back
cd ..
```

## Building a example
For building, flashing and debugging a tool called ss is provided.
For this a soft link is created by the init script.
The usage is very simple. 
Type `./ss ` and you will get a overview of the functionality.
- `./ss build` builds the example
- `./ss flash` flashes the example to the controller
- `./ss oocd_start` starts a open-ocd server. With `make gdb` you get a gdb debug tui.
- `./ss canflash <file>.bin 0x80` flashes the binary via CAN over the ID 0x80
- `./ss oocd_stop` stops the open-ocd server

# Required Sceliton
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

# Examples
- 

## ADC

# ADC

```c
uint16_t led = PIN('C', 1);
uint16_t adc = PIN('A', 2);
```
- Defining pin ids 

---


```c
static void blinky_task(void *args) {
    uint16_t value = 0;
    struct SS_CAN_FRAME msg;
    SS_FEEDBACK rc;
    for (;;) {
        ss_can_frame_set_common(&msg, 0x123, 2);

        rc = ss_adc_read(adc, &value);

        if (rc != SS_FEEDBACK_OK) {
            ss_can_frame_set_signal(&msg, 15, 1, 1);
        } else {
            ss_can_frame_set_signal(&msg, 0, 16, value);
        }

        

        ss_can_send(1, &msg);

        ss_rtos_delay_ms(500);
    }
}
```

- The `blinky_task` function is the FREE-RTOS Function. It contains a `for(;;)` endlos loop, which is delayed with the `ss_rtos_delay_ms` function.
- If the `ss_rtos_delay_ms` is called, all stack-variables `value`, `msg` and `rc`are safed.
- The `ss_can_frame_set_common` function sets the fields of a frame like id and dlc
- The `ss_adc_read` reads the latest adc-value of the defined `adc` pin id. This function is non-blocking. It dont starts a conversion. The `fse_pb_bsp` library periodically startes adc-convertions in the background. 
- The function `ss_can_frame_set_signal` writes a value to a specific interval in the can-message
- With the `ss_can_send` function a can-message is send

---

```c
int main(void)
{
    SS_HANDLE_INIT(ss_init());

    SS_HANDLE_INIT(ss_adc_init(adc));

    SS_HANDLE_INIT(ss_can_init(1, 1000000));

    SS_HANDLE_INIT(ss_rtos_task_add(blinky_task, NULL, 1, "blinky_task"));

    ss_rtos_start();

    while (1) {

	}

    return 0;

}
```

- The function `ss_adc_init` initialises the adc for a given pin. In the background for all pins which are initialized with `ss_adc_init`, the library starts a conversion periodically 
- The function `ss_can_init` initializes a can peripheral with a given baudrate
- With the `ss_rtos_task_add` function a task with a given priority is added to FREE-RTOS

