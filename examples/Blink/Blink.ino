#include <Interrupted.h>
#include <Tasks.h>

#include "config.h"

Semaphore off(1), on(0);
Runner<128> blink;

void setup() {
#ifdef SERIAL
	Serial.begin(SERIAL);
#endif
	Tasks::init();
	Tasks::set_idle_handler(timer_sleep);
	pinMode(LED, OUTPUT);
}

void loop() {
	blink.run([]() {
		on.wait();
#ifdef SERIAL
		Serial.println('0');
#endif
		digitalWrite(LED, LOW);
		Tasks::delay(500);
		off.signal();
	});

	off.wait();
#ifdef SERIAL
	Serial.println('1');
#endif
	digitalWrite(LED, HIGH);
	Tasks::delay(1000);
	on.signal();
}
