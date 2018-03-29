#include <Interrupted.h>
#include <Tasks.h>

#include "config.h"

Channel<char> ch(1);

class Printer: public Task<128> {
	void loop() {
		char c;
		ch.in(c);
#ifdef SERIAL
		Serial.print(c);
#endif
	}
} print;

void setup() {
#ifdef SERIAL
	Serial.begin(SERIAL);
#endif
	Tasks::init();
	Tasks::set_idle_handler(timer_sleep);
	Tasks::start(print);
}

void loop() {
	const char *s = "hello world\r\n";
	char c;
	while (c = *s++) {
		ch.out(c);
		Tasks::delay(1000);
	}
}
