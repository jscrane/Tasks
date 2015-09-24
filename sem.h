#ifndef __SEM_H__
#define __SEM_H__

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

class Semaphore: public semaphore {
public:
	inline void begin(unsigned count) {
		sem_init(this, count);
	}

	inline void signal() {
		sem_signal(this);
	}

	inline void wait() {
		sem_wait(this);
	}
};

#endif
