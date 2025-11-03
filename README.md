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

# update submodule 
git submodule init
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

# Fundamentals
[PIN DEFINITION](docu/pin_definition.md)

[TASK DEFINITION](docu/task_definition.md)

[MAIN SCALITON](docu/main_scaliton.md)

[CAN SEND](docu/can_send.md)

[CAN FILTER](docu/can_filter.md)

[CAN READ](docu/can_read.md)

# Examples
[ADC](adc/README.md)

[BLINKY](blinky/README.md)

[CAN_BOOT](can_boot/README.md)

[CAN_MSG_QUEUE](can_receive_queue/README.md)