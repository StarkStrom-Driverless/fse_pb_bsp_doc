```c
    SS_HANDLE_INIT(ss_can_init(1, 1000000));
    SS_HANDLE_INIT(ss_can_filter_add_msg(1, 0x123));
```

All can-messages which should be recieved have to be added to a filter after init of the
CAN peripharel. For this the function `ss_can_filter_add_msg` can be called for each 
id. The function takes the CAN peripharel id and the message id. 