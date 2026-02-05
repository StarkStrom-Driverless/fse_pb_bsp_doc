#include "ss.h"
#include "ss_pid.h"

void ss_init_error(SS_FEEDBACK feedback);


float get_measurement() {
    return 0.5f;
}



static void controller_task(void *args) {
    struct SS_PID pid = {0};

    /* This function is optional. It sets all controller intern vars to zero to garuentee a smooth start */
    ss_pid_init(&pid);

    /* Set relevant controller parameters */
    pid.ss_pid_period = 0.5f;

    pid.ss_pid_kd = 0.1f;
    pid.ss_pid_kp = 0.8f;
    pid.ss_pid_ki = 0.4f;

    pid.ss_pid_out_max = 1.0f;
    pid.ss_pid_out_min = 0.0f;

    pid.ss_pid_integrator_max = 1.0f;
    pid.ss_pid_integrator_min = -1.0f;

    pid.ss_pid_tau = 0.5f;

    float output_pwm = 0;


    for (;;) {
        /* measure something */
        float measurement = get_measurement();
        
        /* update the controller */
        ss_pid_update(&pid, measurement, &output_pwm);

        /* sleep - this must be the time of pid.ss_pid_period in ms*/
        ss_rtos_delay_ms(500);
    }
}

int main(void)
{
    SS_HANDLE_INIT(ss_init());


    SS_HANDLE_INIT(ss_rtos_task_add(controller_task, NULL, 1, "controller_task"));

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

