Tasks
=====
A simple task library for Arduino, using setjmp/longjmp, inspired by [LWP](https://github.com/jscrane/lwp).

Example
-------
    
    #include <Tasks.h>

    Semaphore off(1), on(0);

    class Blink: public Task<128> {
        void loop() {
            on.wait();
            digitalWrite(0, LOW);
            delay(1000);
            off.signal();
        }
    } blink;

    void setup() {
        Tasks::init();
        Tasks::start(blink);
        pinMode(0, OUTPUT);
    }

    void loop() {
        off.wait();
        digitalWrite(0, HIGH);
        delay(1000);
        on.signal();
    }

Remarks
-------
* There are two tasks, one explicitly created (Blink), and the other implicit 
(the "main task").
* Tasks are of equal priority and run until completion --- until they
run out of things to do; by blocking on a semaphore or other synchronization
object.
* In the example, two tasks coordinate turning an LED off and on using two 
semaphores.

Integration with Interrupted
----------------------------

Interrupted is a library for building low-power, event-driven sketches.
Each sketch has a collection of devices which wake it up under interrupt.

Extending Interrupted for tasks requires a few changes:

- only sleeping the processor when no task is runnable,
- permitting tasks to 'interrupt' each other.

Here's a simple example, for the Arduino Uno:

    #include <Tasks.h>
    #include <taskdevices.h>
    #include <pseudo.h>
    
    #define TIMER   1
    #define SIG     2
    #define LED     13
    
    Signal signal(SIG);
    Watchdog timer(TIMER, 2);
    
    class Ticker: public Task<64> {
    
        TaskDevices devices;
    
        void setup() {
            devices.add(timer);
            devices.begin();
        }
    
        void loop() {
            timer.enable();
            if (devices.select() == TIMER)
                signal.send();
        }
    } ticker;
    
    TaskDevices devices;
    
    void setup(void) {
        Tasks::init();
        Tasks::start(ticker);
        Tasks::set_idle_handler(TaskDevices::on_no_task_runnable);
    
        devices.add(signal);
        devices.begin();
    
        pinMode(LED, OUTPUT);
        digitalWrite(LED, HIGH);
    }
    
    void loop(void) {
        if (devices.select() == SIG)
            digitalWrite(LED, !digitalRead(LED));
    }
    
This example makes use of a Signal, a pseudo-device which can be selected
on, just like a normal interrupting device. One task responds to ticks
of a timer by signalling the other, waking it up to toggle the LED.
