#include <Interrupted.h>
#include <Tasks.h>

#define TIMER	1
#define SIG	2

Signal signal(SIG);
Watchdog timer(TIMER, 1);

class Ticker: public Task<64> {

	TaskDevices devices;

	void setup() {
		devices.add(timer);
		devices.begin();
	}

	void loop() {
		timer.enable();
		if (devices.select() == TIMER)
			signal.send();
	}
} ticker;

TaskDevices devices;

void setup(void) {
	Tasks::init();
	Tasks::start(ticker);
	Tasks::set_idle_handler(TaskDevices::on_no_task_runnable);

	devices.add(signal);
	devices.begin();

	pinMode(RED_LED, OUTPUT);
}

void loop(void) {
	if (devices.select() == SIG)
		digitalWrite(RED_LED, !digitalRead(RED_LED));
}
