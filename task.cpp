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

void task_queue::insert(task *p, task *t) {
	if (p) {
		t->next = p->next;
		p->next = t;
		if (p == _tail)
			_tail = t;
	} else {
		t->next = _head;
		_head = t;
	}
}

task *Tasks::_curr;
task_queue Tasks::_ready;
runnable Tasks::_idle_handler;

void Tasks::reschedule(void) {
	while (_ready.empty())
		_idle_handler();

	task * volatile run = _ready.remove();
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

void task::create(void *stack, void (*entry)()) {
	if (setjmp(context) == 0) {
		unsigned sp = (unsigned)stack, e = (unsigned)entry;
		context[0]._jb[_JBLEN-4] = (sp >> 8);
		context[0]._jb[_JBLEN-5] = (sp & 0xff);
		context[0]._jb[_JBLEN-1] = (e >> 8);
		context[0]._jb[_JBLEN-2] = (e & 0xff);
	}
}
