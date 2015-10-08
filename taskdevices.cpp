#include <setjmp.h>
#include <device.h>
#include "task.h"
#include "taskdevices.h"

#define MODE_NONE	0xffff

unsigned TaskDevices::_mode = MODE_NONE;
task_queue TaskDevices::_sleeping;
bool TaskDevices::_soft_irq;

/*
 * when none of a task's devices is ready: put it to sleep and reschedule.
 */
void TaskDevices::idle(unsigned mode) {
	_mode = _mode == MODE_NONE? mode: Devices::compare_modes(_mode, mode);

	_sleeping.add(Tasks::current());

	Tasks::reschedule();
}

/*
 * when no tasks can run: wait for an interrupt; when we wake, 
 * make all sleeping tasks runnable and return to the scheduler.
 */
void TaskDevices::on_no_task_runnable() {
	if (!_soft_irq)
		Devices::sleep(_mode);

	while (!_sleeping.empty())
		Tasks::ready(_sleeping.remove());

	_soft_irq = false;
}
