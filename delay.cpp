#include <Arduino.h>
#include <stdint.h>
#include <setjmp.h>
#include "task.h"

void Tasks::delay(unsigned long ms) {
	// FIXME: busy waiting
	volatile unsigned long now = millis();
	while (millis() - now < ms) {
		ready(_curr);
		reschedule();
	}
}
