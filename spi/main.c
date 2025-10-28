#include "ss.h"

void ss_init_error(SS_FEEDBACK feedback);



static void spi_task(void *args) {
    uint8_t rx[4] = {0x1, 0x2, 0x3, 0x4};
    uint8_t tx[4] = {0};

    for (;;) {
        ss_spi_rxtx(1, rx, tx, 4);

        ss_rtos_delay_ms(500);
    }
}

int main(void)
{
    SS_HANDLE_INIT(ss_init());

    SS_HANDLE_INIT(ss_spi_init(1, 1000000));

    SS_HANDLE_INIT(ss_rtos_task_add(spi_task, NULL, 1, "spi_task"));

    ss_rtos_start();

    while (1) {

	}

    return 0;

}

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

