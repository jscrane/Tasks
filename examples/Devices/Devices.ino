#include <Interrupted.h>
#include <Tasks.h>
#include <taskdevices.h>

#include "config.h"
#define TIMER	1

Semaphore sem(0);
Watchdog timer(TIMER, TIME);

class Ticker: public Task<128> {

	TaskDevices devices;

	void setup() {
		devices.add(timer);
		devices.begin();
	}

	void loop() {
		timer.enable();
		if (devices.select() == TIMER)
			sem.signal();
	}
} ticker;

void setup(void) {
	Tasks::init();
	Tasks::start(ticker);
	Tasks::set_idle_handler(TaskDevices::on_no_task_runnable);

	pinMode(LED, OUTPUT);
	digitalWrite(LED, HIGH);
}

void loop(void) {
	sem.wait();
	digitalWrite(LED, !digitalRead(LED));
}
