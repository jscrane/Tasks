#include <Interrupted.h>
#include <Tasks.h>

#include "config.h"
Semaphore sem(0);

class Deadlock: public Task<128> {
public:
	void loop() {
#ifdef SERIAL
		Serial.println(F("run"));
#endif
		sem.wait();
	}

} deadlock;

void on_deadlock() {
	interrupts();
	for (;;) {
#ifdef SERIAL
		Serial.println(F("deadlock!"));
#endif
		digitalWrite(LED, HIGH);
		delay(200);
		digitalWrite(LED, LOW);
		delay(300);
	}
}

void setup() {
#ifdef SERIAL
	Serial.begin(SERIAL);
#endif
	Tasks::init();
	Tasks::start(deadlock);
	Tasks::set_idle_handler(on_deadlock);
	pinMode(LED, OUTPUT);
}

void loop() {
	sem.wait();
}
