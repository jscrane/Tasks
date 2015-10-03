#ifndef __TASK_DEVICES_H__
#define __TASK_DEVICES_H__

class TaskDevices: public Devices {
public:
	static void on_no_task_runnable(void);

protected:
	void idle(unsigned mode);

private:
	static task_queue _sleeping;
	static unsigned _mode;
};

#endif
