Devices
-------

This sketch shows how tasks may be used with 
[Interrupted](http://github.com/jscrane/Interrupted).

Two tasks cooperate to flash an led. The ticker waits on a timer
interrupt and signals the shared semaphore when it occurs. The main
task waits on the semaphore and toggles the led when it is released.

Running tasks take priority over device selection. This only happens
when no task is runnable.
