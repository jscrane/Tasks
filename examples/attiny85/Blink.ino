#include <TinyDebugSerial.h>
#include <Tasks.h>

TinyDebugSerial serial;

Semaphore off(1), on(0);

void run() {
	for (;;) {
		on.wait();
		serial.println("0");
		digitalWrite(0, LOW);
		delay(1000);
		off.signal();
	}
}

Task<128> task(run);

void setup() {
	serial.begin(115200);
	Tasks::init();
	task.begin();
	pinMode(0, OUTPUT);
}

void loop() {
	off.wait();
	serial.println("1");
	digitalWrite(0, HIGH);
	delay(1000);
	on.signal();
}
