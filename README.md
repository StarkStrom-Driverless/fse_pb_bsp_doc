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