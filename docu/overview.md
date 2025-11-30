In this chapter, an overview of the system is presented.

![alt text](img/software_pyramid.drawio.png)

The `fse_pb_bsp` library is built on several third-party components.
At the foundation lies the STM32F405RTGE microcontroller.

Because the library depends on the MCU bootloader, the figure shows two pyramids:
the left pyramid represents the bootloader stack, while the right pyramid shows the application stack.

The bootloader is based on Zephyr, a powerful embedded operating system.
It includes MCUboot, a secure bootloader. For this purpose, a separate repository called `fse_pb_bootloader` exists.
Once the bootloader has been successfully compiled and flashed onto the processor board, it usually does not need to be flashed again.

The bootloader requires the following memory layout:

* Bootloader partition
* Slot0 partition
* Slot1 partition

If a valid and correctly signed image is written to the Slot1 partition, the bootloader will swap Slot0 with Slot1 before continuing execution.
By default, the bootloader operates from Slot0.

The right side of the pyramid is based on the libopencm3 library, a low-level configuration library for various microcontroller platforms.
On top of this, the custom-developed `fse_pb_bsp` library provides an abstraction layer for controller configuration.
Additionally, `fse_pb_bsp` relies on FreeRTOS, as it also abstracts the use of the RTOS.

Finally, on top of this stack, the actual application can be developed.

