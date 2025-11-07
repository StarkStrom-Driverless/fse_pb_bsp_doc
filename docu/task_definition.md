
```c
static void task(void *args) {
    uint16_t value = 0;

    for (;;) {
        // do something

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

### Explanation:

* **Task Definition:**
  Each task must be defined as a `static` function with the signature `void task(void *args)`. The `args` parameter is a generic pointer allowing the user to pass data into the task.

* **Task Variables:**
  Variables declared outside the infinite `for(;;)` loop (like `value` in the example) are stored on the task’s dedicated stack, isolated from other tasks.

* **Infinite Loop:**
  Every task contains a `for(;;)` loop to keep it running indefinitely, allowing the RTOS scheduler to manage task switching.

* **Task Delay & Context Switch:**
  At the end of each loop iteration, the task calls `ss_rtos_delay_ms()`, which puts the task into a blocked state for the specified time and triggers a context switch to other ready tasks.

* **Adding Task to Scheduler:**
  The function `ss_rtos_task_add()` registers the task with the FreeRTOS scheduler. It requires:

  * A pointer to the task function.
  * A pointer to user-defined arguments (can be `NULL`).
  * The task priority (higher number means higher priority).
  * A human-readable task name for debugging purposes.

* **Starting the Scheduler:**
  After adding all tasks, `ss_rtos_start()` starts the FreeRTOS scheduler, which begins executing the tasks according to their priorities.

