#ifndef __CHAN_H__
#define __CHAN_H__

template<class T> class Channel: public Selectable {
public:
	Channel(int id): Selectable(id) {}

	void out(T &t) {
		Atomic block;
		if (_t) {
			*_t = t;
			_sig();
		} else
			_wait(t);
	}

	T &in(T &t) {
		Atomic block;
		if (_t) {
			t = *_t;
			_sig();
		} else
			_wait(t);
		return t;
	}

private:
	void _wait(T &t) {
		_t = &t;
		Selectable::ready();
		s.wait();
	}

	void _sig() {
		_t = 0;
		s.signal();
	}

	Semaphore s;
	T *_t;
};

#endif
