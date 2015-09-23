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
                sem_wait(&sem);
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
        sem_signal(&sem);
        task_yield();
    }
