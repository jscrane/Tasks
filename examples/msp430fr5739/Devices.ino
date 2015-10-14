#include <Interrupted.h>
#include <Tasks.h>

#define TIMER	1

Semaphore sem(0);
Watchdog timer(TIMER, 1);

class Ticker: public Task<128> {

	TaskDevices devices;

	void setup() {
		devices.add(timer);
		devices.begin();
	}

	void loop() {
		timer.enable();
		if (devices.select() == TIMER) {
			digitalWrite(GREEN_LED, !digitalRead(GREEN_LED));
			sem.signal();
		}
	}
} ticker;

void setup(void) {
	Tasks::init();
	Tasks::start(ticker);
	Tasks::set_idle_handler(TaskDevices::on_no_task_runnable);

	pinMode(RED_LED, OUTPUT);
	pinMode(GREEN_LED, OUTPUT);
	digitalWrite(RED_LED, HIGH);
}

void loop(void) {
	sem.wait();
	digitalWrite(RED_LED, !digitalRead(RED_LED));
}
