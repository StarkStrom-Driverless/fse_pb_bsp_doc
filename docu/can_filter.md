
```c
SS_HANDLE_INIT(ss_can_init(1, 1000000));
SS_HANDLE_INIT(ss_can_filter_add_msg(1, 0x123));
```

After initializing the CAN peripheral, all CAN messages that need to be received must be added to a filter.
This is done by calling the function `ss_can_filter_add_msg` for each message ID.
The function requires the CAN peripheral ID and the specific message ID to filter.
