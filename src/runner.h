#ifndef __RUNNER_H__
#define __RUNNER_H__

typedef void (*Runnable)(void);

template<unsigned N>
class Runner: public Task<N> {
public:
	void run(Runnable r) {
		if (!_r)
			Tasks::start(*this);
		_r = r;
		s.signal();
	}

	void loop() {
		s.wait();
		_r();
	}

private:
	Runnable _r;
	Semaphore s;
};

#endif
