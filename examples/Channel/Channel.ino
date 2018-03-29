#include <Interrupted.h>
#include <Tasks.h>

#include "config.h"

Channel<char> ch(1);
SerialOut serial(3, 115200);
TaskDevices devices;

const char *s = "hello world\r\n";

class Printer: public Task<128> {
	const char *t;

	void setup() {
		t = s;
	}

	void loop() {
		if (!*t)
			t = s;
		char c = *t++;
		ch.out(c);
	}
} print;

void setup() {
	serial.enable();
	devices.add(serial);
	devices.add(ch);
	devices.begin();

	Tasks::init();
	Tasks::set_idle_handler(TaskDevices::on_no_task_runnable);
	Tasks::start(print);
}

void loop() {
	char c[2];
	c[1] = '\0';
	if (devices.select() == 1) {
		ch.in(c[0]);
		serial.write(c);
	}
}
