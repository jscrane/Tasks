#include <TinyDebugSerial.h>
#include <Tasks.h>

TinyDebugSerial serial;

Semaphore off(1), on(0);

void deadlock() {
	serial.println("deadlock!");
	digitalWrite(0, HIGH);
	delay(200);
	digitalWrite(0, LOW);
	delay(300);
}

task_queue delaying;

// static member on Task: statics => operate on current task
// in separate file: sleep.cpp. how to initialise?
void task_sleep(unsigned long ms) {
	unsigned long now = millis();
	task *p, *q;
	for (p = 0, q = delaying.head(); q; p = q, q = q->next) {
		unsigned long qms = q->wake - now;
		if (qms > ms)
			break;
	}
	task *t = task::current();
	t->wake = now + ms;
	delaying.insert(p, t);
	Tasks::reschedule();
}

void idle() {
	if (delaying.empty())
		deadlock();
	else {
		task *t = delaying.remove();
		delay(t->wake - millis());
		Tasks::ready(t);
	}
}

void run() {
	for (;;) {
		on.wait();
		serial.println("0");
		digitalWrite(0, LOW);
		task_sleep(1000);
		off.signal();
	}
}

Task<128> task(run);

void setup() {
	serial.begin(115200);
	serial.println("hello world");
	Tasks::init();
	Tasks::ready(&task);
	Tasks::set_idle_handler(idle);
	pinMode(0, OUTPUT);
}

void loop() {
	off.wait();
	serial.println("1");
	digitalWrite(0, HIGH);
	task_sleep(1000);
	on.signal();
}
