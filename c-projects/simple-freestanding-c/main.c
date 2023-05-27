#ifdef __x86_64__
# include "unistd_64.h"
#else
# include "unistd_32.h"
#endif

#include "syscall.h"

void _start(){
	write(1, "Hewwo wowwd from no libc :3\n", 28);
	_exit(0);
}
