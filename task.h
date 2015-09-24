#ifndef __TASK_H__
#define __TASK_H__

typedef struct task {
	struct task *next;
	jmp_buf context;
} task_t;

extern task_t *curr;

typedef struct task_queue {
	task_t *head, *tail;
} task_queue_t;

extern task_queue_t ready;

task_t *queue_remove(task_queue_t *q);

void queue_add(task_queue_t *q, task_t *t);

void task_reschedule(void);

/*
 * initialises the task library: call from setup().
 */
void task_init(void);

/*
 * creates a new task, with task block, stack pointer and entry-point.
 */
void task_create(task_t *t, void *stack, void (*entry)());

/*
 * yields control to another (ready) task.
 */
void task_yield(void);

#endif
