#include <Interrupted.h>
#include <Tasks.h>

Semaphore off(1), on(0);

class Blink: public Task<64> {
	void loop() {
		on.wait();
		digitalWrite(GREEN_LED, !digitalRead(GREEN_LED));
		delay(1000);
		off.signal();
	}
} blink;

void setup() {
	Tasks::init();
	Tasks::start(blink);
	pinMode(RED_LED, OUTPUT);
	pinMode(GREEN_LED, OUTPUT);
}

void loop() {
	off.wait();
	digitalWrite(RED_LED, !digitalRead(RED_LED));
	delay(1000);
	on.signal();
}
