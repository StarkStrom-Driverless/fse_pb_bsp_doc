#include "ss.h"
#include "ss_fsm.h"

void ss_init_error(SS_FEEDBACK feedback);


enum EVENTS {
    EVENT_START_A,
    EVENT_STOP_A,
    EVENT_START_B,
    EVENT_STOP_B
};

static void a_task(void *args) {

    ss_fsm_event_add(EVENT_START_A);
    ss_fsm_event_add(EVENT_STOP_A);

    enum STATE {
        ON,
        OFF
    };

    enum STATE state = OFF;

    for (;;) {

        int16_t event = ss_fsm_event_receive(NULL);

        switch(event) {
            case EVENT_START_A: 
                state = ON;
                ss_fsm_event_send_core(event);
                break;

            case EVENT_STOP_A:
                state = OFF;
                ss_fsm_event_send_core(event);
                break;

            default:
                break;
        }


        switch(state) {
            case ON:
                ss_led_heartbeat_toggle();
                break;

            case OFF:
                ss_led_heartbeat_off();
                break;

            default: break;
        }

        ss_rtos_delay_ms(500);
    }
}

static void b_task(void *args) {

    ss_fsm_event_add(EVENT_START_B);
    ss_fsm_event_add(EVENT_STOP_B);

    enum STATE {
        ON,
        OFF
    };

    enum STATE state = OFF;

    for (;;) {

        int16_t event = ss_fsm_event_receive(NULL);

        switch(event) {
            case EVENT_START_B: 
                state = ON;
                ss_fsm_event_send_core(event);
                break;

            case EVENT_STOP_B:
                state = OFF;
                ss_fsm_event_send_core(event);
                break;

            default:
                break;
        }

        switch(state) {
            case ON:
                ss_led_dbg1_toggle();
                break;

            case OFF:
                ss_led_dbg1_off();
                break;

            default: break;
        }

        ss_rtos_delay_ms(200);
    }
}

static void main_task(void *args) {
    enum STATES {
        IDLE,
        STOP_A,
        START_B,
        STOP_B,
        START_A
    };

    enum STATES state = IDLE;
    enum STATES new_state = state;

    for (;;) {
        int16_t event = ss_fsm_event_receive_core();

        switch(state) {
            case IDLE:
                new_state = STOP_A;
                break;

            case STOP_A:
                ss_fsm_event_send(EVENT_STOP_A);
                if (event == EVENT_STOP_A) {
                    new_state = START_B;
                }
                break;

            case START_B:
                ss_fsm_event_send(EVENT_START_B);
                if (event == EVENT_START_B) {
                    new_state = STOP_B;
                }
                break;

            case STOP_B:
                ss_fsm_event_send(EVENT_STOP_B);
                if (event == EVENT_STOP_B) {
                    new_state = START_A;
                }
                break;

            case START_A:
                ss_fsm_event_send(EVENT_START_A);
                if (event == EVENT_START_A) {
                    new_state = STOP_A;
                }
                break;

            default : break;
        }



        ss_rtos_delay_ms(2000);


        state = new_state;
    }
}

int main(void)
{
    SS_HANDLE_INIT(ss_init());


    SS_HANDLE_INIT(ss_rtos_task_add(a_task, NULL, 1, "a_task"));
    SS_HANDLE_INIT(ss_rtos_task_add(b_task, NULL, 1, "b_task"));
    SS_HANDLE_INIT(ss_rtos_task_add(main_task, NULL, 1, "main_task"));


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

