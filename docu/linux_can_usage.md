This section shows how to use the PEAK-System PCAN-USB-PRO Interface

```shell
sudo ip link set can0 up type can bitrate 1000000
```
This command enables can0 with a bitrate of 1MBaud.
`ip a` shows can0 and can1. can0 should show now type UP.

With `cansend can0 <data>` messages can be send and with 
`candump can0` incomming messages can be displayed
