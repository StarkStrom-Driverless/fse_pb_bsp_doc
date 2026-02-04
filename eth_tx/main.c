#include "ss.h"

void ss_init_error(SS_FEEDBACK feedback);


/**
 * Define a global payload which contains 1500 bytes 
 */
struct SS_ETH_PAYLOAD payload;


static void eth_task(void *args) {

    /* Define a pointer which points to the ethernet interface */
    struct SS_ETH_INTF* intf;

    /* This will return the interface for the udp port 6301*/
    ss_eth_get(6301, &intf);

    /* Setup payload header */
    ss_eth_cpy_ip_style(payload.id.ip, SS_ETH_IP(192, 168, 10, 122), 4);
    payload.id.port = 6301;

    for (;;) {

        /* Set payload */
        payload.buffer[0] = 0xA;
        payload.buffer[1] = 0xF;
        payload.buffer[2] = 0xF;
        payload.buffer[3] = 0xE;

        /* Set length of payload */
        payload.buffer_len = 4;

        /* send payload */
        ss_eth_send(intf, &payload);

        ss_led_heartbeat_toggle();

        ss_rtos_delay_ms(1000);
    }
}

int main(void)
{
    SS_HANDLE_INIT(ss_init());

    /**
     * Init w5500 based ethernet interface with ip, netmask, mac, and gateway-address
     */
    SS_HANDLE_INIT(ss_eth_init(
        SS_ETH_IP(192, 168, 10, 104),
        SS_ETH_IP(255, 255, 0, 0),
        SS_ETH_MAC(0x00, 0x08, 0xDC, 0xAB, 0xCD, 0xEF),
        SS_ETH_IP(192, 168, 10, 1)
    ));

    /**
     * Add a udp socket to the eth interface with a port
     * Provice the payload as a pointer
     */
    SS_HANDLE_INIT(ss_eth_socket_udp_add(6301, &payload));

    SS_HANDLE_INIT(ss_rtos_task_add(eth_task, NULL, 1, "eth_task"));

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

