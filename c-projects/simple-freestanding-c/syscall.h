extern int pl_syscall(int syscall, int paramNum, void* params);

int write(int fd, void* data, int len){
	void* ptr[3] = { (int*)fd, data, (int*)len };
	return pl_syscall(__NR_write, 3, ptr);
}

void _exit(int code){
	void* ptr[1] = { (int*)code };
	pl_syscall(__NR_exit, 1, ptr);
}
