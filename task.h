#ifndef __TASK_H__
#define __TASK_H__

typedef struct task {
	struct task *next;
	jmp_buf context;
};

extern task *curr;

class task_queue {
public:
	task_queue() { _head = _tail = 0; }

	task *remove();

	void add(task *t);

	inline bool empty() { return _head == 0; }

private:
	task *_head, *_tail;
};

extern task_queue ready;

/*
 * creates a new task, with task block, stack pointer and entry-point.
 */
void task_create(task *t, void *stack, void (*entry)());

template<unsigned N>
class Task: public task {
public:
	Task(void (*entry)()) {
		task_create(this, &_stack[N-1], entry);
	}

	inline void begin() {
		ready.add(this);
	}

private:
	unsigned _stack[N];
};

class Tasks {
public:
	/*
	 * initialises the task library: call from setup().
	 */
	static void init(void);

	/*
	 * yields control to another (ready) task.
	 */
	static void yield(void);

	static void reschedule(void);
};

#endif
