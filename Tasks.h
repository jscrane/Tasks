#ifndef __TASK_H__
#define __TASK_H__

typedef struct task {
	struct task *next;
	jmp_buf context;
	void *env;
} task_t;

typedef struct task_queue {
	task_t *head, *tail;
} task_queue_t;

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

typedef struct semaphore {
	task_queue_t waiting;
	unsigned count;
} sem_t;

/*
 * initialises a (counting) semaphore.
 */
void sem_init(sem_t *s, unsigned count);

/*
 * if the semaphore's count is positive, decrements it and continues,
 * otherwise blocks.
 */
void sem_wait(sem_t *s);

/*
 * if a task is waiting on the semaphore, releases it, otherwise
 * increments its count.
 */
void sem_signal(sem_t *s);

#endif
