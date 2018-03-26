#ifndef __SELECTABLE_H__
#define __SELECTABLE_H__

class Selectable: public Device {
public:
	bool begin() { return true; }

	void ready() {
		Device::ready();
		if (is_enabled())
			TaskDevices::soft_irq();
	}

protected:
	Selectable(int id): Device(id) {}

	void _enable(bool e) {}
};

#endif
