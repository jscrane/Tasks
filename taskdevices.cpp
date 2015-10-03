#include <setjmp.h>
#include <device.h>
#include "task.h"
#include "taskdevices.h"

unsigned TaskDevices::_mode;
task_queue TaskDevices::_sleeping;

// when none of a task's devices is ready: 
// put it to sleep and reschedule
void TaskDevices::idle(unsigned mode) {
	_mode = Devices::compare_modes(_mode, mode);
	_sleeping.add(Tasks::current());
	Tasks::reschedule();
}

// when no tasks can run: wait for an interrupt; when we wake, 
// make all sleeping tasks runnable and reschedule
void TaskDevices::on_no_task_runnable() {
	Devices::sleep(_mode);
	while (!_sleeping.empty())
		Tasks::ready(_sleeping.remove());
	Tasks::reschedule();
}
