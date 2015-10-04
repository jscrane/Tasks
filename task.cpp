#include <setjmp.h>
#include "task.h"

task *task_queue::remove() {
	task *t = _head;
	_head = t->next;
	if (empty())
		_tail = 0;
	return t;
}

void task_queue::add(task *t) {
	if (_tail)
		_tail->next = t;
	else
		_head = t;
	_tail = t;
	t->next = 0;
}

task *Tasks::_curr;
task_queue Tasks::_ready;
runnable Tasks::_idle_handler;

void Tasks::reschedule(void) {
	task * volatile run;
	while (!(run = _ready.remove()))
		_idle_handler();

	if (run != _curr)
		if (setjmp(_curr->context) == 0) {
			_curr = run;
			longjmp(_curr->context, 1);
		}
}

void Tasks::init(void) {
	static task main;
	_curr = &main;
}

void task::entry() {
	task * volatile t = Tasks::current();
	t->setup();
	for (;;)
		t->loop();
}

void task::create(void *stack) {
	setjmp(context);
	unsigned sp = (unsigned)stack, e = (unsigned)entry;
	context[0]._jb[_JBLEN-4] = (sp >> 8);
	context[0]._jb[_JBLEN-5] = (sp & 0xff);
	context[0]._jb[_JBLEN-1] = (e >> 8);
	context[0]._jb[_JBLEN-2] = (e & 0xff);
}
