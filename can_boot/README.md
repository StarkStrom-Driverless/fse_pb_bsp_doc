This example builds upon the **blinky** example.
Its purpose is to demonstrate the **firmware flashing mechanism over CAN** by changing the blinking frequency of the LED.

---

```c
SS_HANDLE_INIT(ss_canboot_init(0x80, 0x08080000));
```

The `ss_canboot_init()` function initializes the system to receive firmware updates via CAN.
The **ss-tool** transmits a complete binary file to the controller, word by word, using a single CAN identifier.
In this example, CAN ID **`0x80`** is used.

The **ss_canboot** module then writes the received data segments to a designated flash area, defined by the offset **`0x08080000`**.
Once the entire image has been successfully received, a **power cycle** is required to trigger the **MCUBoot swap process** and apply the update.

Currently, `ss_canboot_init()` introduces a **1-second delay during startup**, as the flash area is erased during initialization.

![alt text](img/canboot.drawio.png)
