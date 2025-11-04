The following example shows how to use the spi interface.

```c
SS_HANDLE_INIT(ss_spi_init(1, 1000000));
```
The function `ss_spi_init` initialsies a spi peripharel.
For this, it takes the id of the peripharel (in this case SPI1) and 
the baudrate for transfering data.

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

- [Task definition according to TASK DEFINITION](../docu/task_definition.md)

With the function `ss_spi_rxtx` a transmition is started. For this the peripherel id is
provided. for providing the tx-data, the pointer to the array tx is passed. For 
telling the fuction where to write the returnd data, the pointer to the rx array is
provided. The last parameter is the size of the arrays. This will start a spi-rxtx action
which returns 4 bytes of data 
