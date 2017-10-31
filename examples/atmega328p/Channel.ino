#include <Interrupted.h>
#include <Tasks.h>

Channel<char> ch;

class Printer: public Task<128> {
	void loop() {
		char c;
		ch.in(c);
		Serial.print(c);
	}
} print;

void setup() {
	Serial.begin(115200);
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
