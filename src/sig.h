#ifndef __SIG_H__
#define __SIG_H__

class Signal: public Selectable {
public:
	Signal(int id): Selectable(id) {}

	void send() { ready(); }
};

#endif
