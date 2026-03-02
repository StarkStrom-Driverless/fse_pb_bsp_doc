This code [main.c](main.c) demonstrats the use of receiving can-frames

---

The behaviour of this example is, that if you send a frame with the id 0x123, the blue led is changing state instant and the green led in a interval of 5 seconds.
This is achieved by receiving this message in two different tasks.

