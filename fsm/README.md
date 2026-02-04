in this code [main.c](main.c) a fsm is implemented.
The idea behind this is, that you have a central main task which executes a global fsm.
This main task sends and receives messages to other tasks. 
Other tasks (such as a_task or b_task) receives the messages from main and change there own small fsm or something else.

