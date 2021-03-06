#include <Interrupted.h>
#include <Tasks.h>

#include "config.h"

Semaphore forks[MAX];
static byte ids = 1;
static byte leds[] = { LED1, LED2, LED3, LED4, LED5 };

void eating(byte id, byte weight) {
#ifdef SERIAL
	Serial.print(F("Philosopher "));
	Serial.print(id);
	Serial.print(F(" eats: "));
	Serial.println(weight);
#endif

	digitalWrite(leds[id], HIGH);

	Tasks::delay(1 + random(MAX * 100));

	digitalWrite(leds[id], LOW);
}

class Philosopher: public Task<50> {
public:
	void setup() {
		_id = ids++;
	}

	void loop() {
		forks[_id - 1].wait();
		forks[_id].wait();

		eating(_id, _w++);

		forks[_id - 1].signal();
		forks[_id].signal();
	}

private:
	byte _id, _w;
};

Philosopher philosophers[MAX-1];

void setup() {
#ifdef SERIAL
	Serial.begin(SERIAL);
#endif

	Tasks::init();
	Tasks::set_idle_handler(timer_sleep);
	for (int i = 0; i < MAX; i++) {
		forks[i].signal();
		pinMode(leds[i], OUTPUT);
	}
	for (int i = 0; i < MAX-1; i++)
		Tasks::start(philosophers[i]);
}

void loop() {
	static byte weight;

	forks[0].wait();
	forks[MAX-1].wait();

	eating(0, weight++);

	forks[0].signal();
	forks[MAX-1].signal();
}
