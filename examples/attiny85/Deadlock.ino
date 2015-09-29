#include <TinyDebugSerial.h>
#include <Tasks.h>

TinyDebugSerial serial;

Semaphore sem(0);

void run() {
	for (;;) {
		serial.println("run");
		sem.wait();
	}
}

Task<128> task(run);

void deadlock() {
	serial.println("deadlock!");
	digitalWrite(0, HIGH);
	delay(200);
	digitalWrite(0, LOW);
	delay(300);
}

void setup() {
	serial.begin(115200);
	serial.println("hello world");
	Tasks::init();
	Tasks::ready(&task);
	Tasks::set_idle_handler(deadlock);
	pinMode(0, OUTPUT);
}

void loop() {
	sem.wait();
}
