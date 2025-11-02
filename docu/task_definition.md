```c
static void task(void *args) {
    uint16_t value = 0;

    for (;;) {
        // dosomething

        ss_rtos_delay_ms(500);
    }
}

int main(void)
{
    SS_HANDLE_INIT(ss_init());

    SS_HANDLE_INIT(ss_rtos_task_add(task, NULL, 1, "task"));

    ss_rtos_start();

    while (1) {

	}

    return 0;

}
```

A task definition needs a static global function. 
The function has a not specified transfer paramter.
All defined variables outside the `for(;;)`-loop stored on a task specific stack.
Every task has a `for(;;)`-loop.
At the end of every cycle of this loop the function `ss_rtos_delay_ms()` must be executed.
This function triggers a change of context and delays the task.

The function `ss_rtos_task_add()` addes a task to the FreeRtos schedular.
It takes a function pointer to the task.
A pointer to a user-defined struct which is passed to the task by FreeRtos with `void *args`
The priority of the task and the name
 