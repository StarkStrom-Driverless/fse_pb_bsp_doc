This example demonstrates how to use the SPI interface.

```c
SS_HANDLE_INIT(ss_spi_init(1, 1000000));
```

The function `ss_spi_init` initializes an SPI peripheral.
It takes the peripheral ID (in this case, SPI1) and the desired baud rate for data transfer.

---

```c
static void spi_task(void *args) {
    uint8_t rx[4] = {0x1, 0x2, 0x3, 0x4};
    uint8_t tx[4] = {0};

    for (;;) {
        ss_spi_rxtx(1, rx, tx, 4);

        ss_rtos_delay_ms(500);
    }
}
```

* [Task definition according to TASK DEFINITION](../docu/task_definition.md)

The function `ss_spi_rxtx` initiates a SPI transmission and reception.
It requires the peripheral ID, a pointer to the buffer for receiving data (`rx`), a pointer to the buffer containing data to send (`tx`), and the size of the data in bytes.
In this example, 4 bytes are transmitted and received each cycle.
