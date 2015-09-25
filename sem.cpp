#include <setjmp.h>
#include "task.h"
#include "sem.h"

void Semaphore::wait() {
	if (_count == 0) {
		_waiting.add(Tasks::current());
		Tasks::reschedule();
	} else
		_count--;
}

void Semaphore::signal() {
	if (_waiting.empty())
		_count++;
	else
		Tasks::ready(_waiting.remove());
}

