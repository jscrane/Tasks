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

task *curr;
task_queue ready;

void Tasks::reschedule(void) {
	task * volatile run = ready.remove();

	if (run != curr)
		if (setjmp(curr->context) == 0) {
			curr = run;
			longjmp(curr->context, 1);
		}
}

void Tasks::yield(void) {
	ready.add(curr);
	reschedule();
}

void Tasks::init(void) {
	static task main;
	curr = &main;
}

void task_create(task *t, void *stack, void (*entry)()) {
	if (setjmp(t->context) == 0) {
		unsigned sp = (unsigned)stack, e = (unsigned)entry;
		t->context[0]._jb[_JBLEN-4] = (sp >> 8);
		t->context[0]._jb[_JBLEN-5] = (sp & 0xff);
		t->context[0]._jb[_JBLEN-1] = (e >> 8);
		t->context[0]._jb[_JBLEN-2] = (e & 0xff);
	}
}
