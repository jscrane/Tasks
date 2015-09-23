#include <setjmp.h>
#include "Tasks.h"

static task_t *remove(task_queue_t *q) {
	task_t *t = q->head;
	q->head = t->next;
	if (!q->head)
		q->tail = 0;
	return t;
}

static void add(task_queue_t *q, task_t *t) {
	if (q->tail)
		q->tail->next = t;
	else
		q->head = t;
	q->tail = t;
	t->next = 0;
}

static task_t *curr;
static task_queue_t ready;

static void reschedule(void) {
	task_t * volatile run = remove(&ready);

	if (run != curr)
		if (setjmp(curr->context) == 0) {
			curr = run;
			longjmp(curr->context, 1);
		}
}

void task_yield(void) {
	add(&ready, curr);
	reschedule();
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
		add(&ready, t);
	}
}

void sem_init(sem_t *s, unsigned count) {
	s->count = count;
	s->waiting.head = s->waiting.tail = 0;
}

void sem_wait(sem_t *s) {
	if (s->count == 0) {
		add(&s->waiting, curr);
		reschedule();	
	} else
		s->count--;
}

void sem_signal(sem_t *s) {
	if (s->waiting.head)
		add(&ready, remove(&s->waiting));
	else
		s->count++;
}

