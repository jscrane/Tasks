#include <setjmp.h>
#include "task.h"
#include "sem.h"

void sem_init(sem_t *s, unsigned count) {
	s->count = count;
	s->waiting.head = s->waiting.tail = 0;
}

void sem_wait(sem_t *s) {
	if (s->count == 0) {
		queue_add(&s->waiting, curr);
		task_reschedule();	
	} else
		s->count--;
}

void sem_signal(sem_t *s) {
	if (s->waiting.head)
		queue_add(&ready, queue_remove(&s->waiting));
	else
		s->count++;
}

