#include <stdint.h>
#include <setjmp.h>
#include "task.h"

void task::create(void *stack) {
	setjmp(_context);
	
	// jmpbuf register names are inconsistent with setjmp/longjmp
	_context[0].__j_r11 = (uint32_t)entry;
	_context[0].__j_pc = (uint32_t)stack;
}
