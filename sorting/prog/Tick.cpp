#include "Tick.h"



__int64 tick(void) {
	__int64 Value = 0;
	__asm {
		RDTSC
		MOV		DWORD PTR[Value], EAX
		MOV		DWORD PTR[Value + 4], EDX
	}

	return Value;
}
