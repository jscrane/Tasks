#include <TinyDebugSerial.h>
#include <Tasks.h>

TinyDebugSerial serial;

Semaphore off(1), on(0);

class Blink: public Task<128> {
public:
	void loop() {
		on.wait();
		serial.println("0");
		digitalWrite(0, LOW);
		delay(1000);
		off.signal();
	}
} blink;

void setup() {
	serial.begin(115200);
	Tasks::init();
	Tasks::ready(blink);
	pinMode(0, OUTPUT);
}

void loop() {
	off.wait();
	serial.println("1");
	digitalWrite(0, HIGH);
	delay(1000);
	on.signal();
}
