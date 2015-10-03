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
        Tasks::ready(blink);
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
* There are two tasks, one explicitly created, and the other implicit (i.e., 
the "main task").
* Tasks are of equal priority and run until completion, i.e., until they
run out of things to do; by blocking on a semaphore or other synchronization
object.
* In the example, two tasks coordinate turning an LED off and on using two 
semaphores.
