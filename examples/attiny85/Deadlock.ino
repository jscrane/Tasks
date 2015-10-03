#include <TinyDebugSerial.h>
#include <Interrupted.h>
#include <Tasks.h>

TinyDebugSerial serial;

Semaphore sem(0);

class Deadlock: public Task<128> {
public:
	void loop() {
		serial.println("run");
		sem.wait();
	}

} deadlock;

void on_deadlock() {
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
	Tasks::ready(deadlock);
	Tasks::set_idle_handler(on_deadlock);
	pinMode(0, OUTPUT);
}

void loop() {
	sem.wait();
}
