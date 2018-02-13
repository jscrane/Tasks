#include <Interrupted.h>
#include <Tasks.h>

#include "config.h"

Semaphore off(1), on(0);

class Blink: public Task<128> {
	void loop() {
		on.wait();
#ifdef SERIAL
		Serial.println('0');
#endif
		digitalWrite(LED, LOW);
		Tasks::delay(1000);
		off.signal();
	}
} blink;

void setup() {
#ifdef SERIAL
	Serial.begin(SERIAL);
#endif
	Tasks::init();
	Tasks::set_idle_handler(timer_sleep);
	Tasks::start(blink);
	pinMode(LED, OUTPUT);
}

void loop() {
	off.wait();
#ifdef SERIAL
	Serial.println('1');
#endif
	digitalWrite(LED, HIGH);
	Tasks::delay(1000);
	on.signal();
}
