#include <TinyDebugSerial.h>
#include <setjmp.h>
#include <Tasks.h>

TinyDebugSerial serial;
static task_t task;
static word stack[128];
static sem_t sem;

void run() {
	for (;;) {
		serial.println("0");
		digitalWrite(0, LOW);
		delay(1000);
		sem_signal(&sem);
		task_yield();
	}
}

void setup() {
	serial.begin(115200);
	task_init();
	task_create(&task, &stack[127], run);
	sem_init(&sem, 0);
	pinMode(0, OUTPUT);
}

void loop() {
	serial.println("1");
	digitalWrite(0, HIGH);
	delay(1000);
	sem_wait(&sem);
}
