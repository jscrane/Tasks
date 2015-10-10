#include <stdint.h>
#include <setjmp.h>
#include "task.h"

void task::create(void *stack) {
	setjmp(_context);
	unsigned sp = (unsigned)stack, e = (unsigned)entry;
	_context[0]._jb[_JBLEN-4] = (sp >> 8);
	_context[0]._jb[_JBLEN-5] = (sp & 0xff);
	_context[0]._jb[_JBLEN-1] = (e >> 8);
	_context[0]._jb[_JBLEN-2] = (e & 0xff);
}
