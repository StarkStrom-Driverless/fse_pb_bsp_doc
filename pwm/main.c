#include "ss.h"


void ss_init_error(SS_FEEDBACK feedback);


uint16_t led = PIN('A', 15);

static void pwm_task(void *args) {
    
    
    uint8_t value = 50;
    uint8_t direction = 0;
    

    for (;;) {
        ss_pwm_write(led, value);
        
        if (direction == 0) {
            if (value < 100) {
                value++;
            } else {
                direction = 1;
            } 
        } else {
            if (value > 0) {
                value--;
            }else{
                direction = 0;
            }
        }

        ss_rtos_delay_ms(10);
    }
}

int main(void)
{
    SS_HANDLE_INIT(ss_init());
    SS_HANDLE_INIT(ss_pwm_init(led, 10000));
    SS_HANDLE_INIT(ss_rtos_task_add(pwm_task, NULL, 1, "pwm_task"));

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

