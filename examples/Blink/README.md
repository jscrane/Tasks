Blink
-----

The classic Blink sketch, now with tasks!

One task turns the LED on and the other turns it off. They cooperate
using a pair of semaphores.

This example also shows the use of per-task delays, rather than the
Arduino delay API which sleeps the whole sketch. Compare this with
the approach encouraged by the Interrupted library in the Devices
sketch.
