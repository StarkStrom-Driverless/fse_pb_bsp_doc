```c
static void task(void *args) {
    uint16_t value = 0;

    for (;;) {
        // dosomething

        ss_rtos_delay_ms(500);
    }
}
```

A task definition needs a static global function. 
The function has a not specified transfer paramter.
All defined variables outside the `for(;;)`-loop stored on a task specific stack.
Every task has a `for(;;)`-loop.
At the end of every cycle of this loop the function `ss_rtos_delay_ms()` must be executed.
This function triggers a change of context and delays the task.
 