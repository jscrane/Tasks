#include <Interrupted.h>
#include <Tasks.h>

#include "config.h"

Channel<char> ch;

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
	Tasks::start(print);
}

void loop() {
	const char *s = "hello world\r\n";
	char c;
	while (c = *s++) {
		ch.out(c);
		delay(1000);
	}
}
