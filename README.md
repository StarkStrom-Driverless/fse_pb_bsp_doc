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

## Preparing all existing examples
```shell

# update submodule in the base dir
git submodule update
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

# Overview
[PIN CAPABILITYS](docu/pin_capabilities.md)

[INSTALL](docu/install.md)

[CAN USAGE](docu/linux_can_usage.md)

# Fundamentals
[PIN DEFINITION](docu/pin_definition.md)

[TASK DEFINITION](docu/task_definition.md)

[MAIN SCALITON](docu/main_scaliton.md)

[CAN SEND](docu/can_send.md)

[CAN FILTER](docu/can_filter.md)

[CAN READ](docu/can_read.md)

# Examples
[BLINKY](blinky/README.md)

[INPUT](input/README.md)

[ADC](adc/README.md)

[CAN_BOOT](can_boot/README.md)

[READ CAN_MSGS](can_receive_std/README.md)

[READ CAN_MSG_QUEUES](can_receive_queue/README.md)

[CAN TIMEOUT DETECTION](can_tod/README.md)

[PWM](pwm/README.md)

[FREQUENCY MEASUREMENT](fm/README.md)

[SPI](spi/README.md)

[INPUT OBSERVATION](iob/README.md)