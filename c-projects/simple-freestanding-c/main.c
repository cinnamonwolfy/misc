#include "syscall.h"

void _start(){
	write(1, "Hewwo wowwd from no libc :3\n", 28);
	_exit(0);
}
