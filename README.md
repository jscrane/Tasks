Tasks
=====
A simple task library for Arduino, using setjmp/longjmp inspired by [LWP](https://github.com/jscrane/lwp).

Example
-------
    
    #include <setjmp.h>
    #include <Tasks.h>

    static task_t task;
    static word stack[128];
    static sem_t sem;

    void run() {
        for (;;) {
                digitalWrite(0, LOW);
                delay(1000);
        	sem_signal(&sem);
        	task_yield();
        }
    }

    void setup() {
        task_init();
        task_create(&task, &stack[127], run);
        sem_init(&sem, 0);
        pinMode(0, OUTPUT);
    }

    void loop() {
        digitalWrite(0, HIGH);
        delay(1000);
        sem_wait(&sem);
    }

Remarks
-------
* There are two tasks, one explicitly created, and the other implicit (i.e., 
the "main task").
* Tasks are of equal priority and run until completion, i.e., until they
run out of things to do; by blocking on a semaphore or explicitly yielding
the processor.
* In the example, the main thread switches on an LED on PB0 (this is an
ATtiny85), delays for a second and blocks on the semaphore.
* When the second thread runs, it turns off the LED and sleeps for a second
before releasing the main thread and yielding to it.
