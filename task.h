#ifndef __TASK_H__
#define __TASK_H__

class task {
public:
	struct task *next;
	jmp_buf context;

	void create(void *stack, void (*entry)());
};

template<unsigned N>
class Task: public task {
public:
	Task(void (*entry)()) {
		create(&_stack[N-1], entry);
	}

private:
	unsigned _stack[N];
};

class task_queue {
public:
	task_queue() { _head = _tail = 0; }

	task *remove();

	void add(task *t);

	inline bool empty() { return _head == 0; }

private:
	task *_head, *_tail;
};

class Tasks {
public:
	/*
	 * initialises the task library: call from setup().
	 */
	static void init(void);

	/*
	 * makes a task runnable.
	 */
	static inline void ready(task *t) {
		_ready.add(t);
	}

	/*
	 * yields control to another (ready) task.
	 */
	static inline void yield(void) {
		ready(_curr);
		reschedule();
	}

	static inline task *current(void) {
		return _curr;
	}

	static void reschedule(void);

private:
	static task *_curr;
	static task_queue _ready;
};

#endif
