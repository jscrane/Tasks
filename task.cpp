#include <setjmp.h>
#include "task.h"

task_t *queue_remove(task_queue_t *q) {
	task_t *t = q->head;
	q->head = t->next;
	if (!q->head)
		q->tail = 0;
	return t;
}

void queue_add(task_queue_t *q, task_t *t) {
	if (q->tail)
		q->tail->next = t;
	else
		q->head = t;
	q->tail = t;
	t->next = 0;
}

task_t *curr;
task_queue_t ready;

void task_reschedule(void) {
	task_t * volatile run = queue_remove(&ready);

	if (run != curr)
		if (setjmp(curr->context) == 0) {
			curr = run;
			longjmp(curr->context, 1);
		}
}

void task_yield(void) {
	queue_add(&ready, curr);
	task_reschedule();
}

void task_init(void) {
	static task_t main;
	curr = &main;
}

void task_create(task_t *t, void *stack, void (*entry)()) {
	if (setjmp(t->context) == 0) {
		unsigned sp = (unsigned)stack, e = (unsigned)entry;
		t->context[0]._jb[_JBLEN-4] = (sp >> 8);
		t->context[0]._jb[_JBLEN-5] = (sp & 0xff);
		t->context[0]._jb[_JBLEN-1] = (e >> 8);
		t->context[0]._jb[_JBLEN-2] = (e & 0xff);
	}
}
