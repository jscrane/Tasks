#include <Interrupted.h>
#include <Tasks.h>

#define LED	13

Semaphore off(1), on(0);

class Blink: public Task<128> {
	void loop() {
		on.wait();
		Serial.println("0");
		digitalWrite(LED, LOW);
		delay(1000);
		off.signal();
	}
} blink;

void setup() {
	Serial.begin(115200);
	Tasks::init();
	Tasks::start(blink);
	pinMode(LED, OUTPUT);
}

void loop() {
	off.wait();
	Serial.println("1");
	digitalWrite(LED, HIGH);
	delay(1000);
	on.signal();
}
