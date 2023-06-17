.text
.intel_syntax noprefix
.globl pl_syscall

pl_syscall:
	mov		rax, rdi
	mov		r11, rsi
	mov		rcx, rdx

	cmp		r11, 6
	je		args6
	cmp		r11, 5
	je		args5
	cmp		r11, 4
	je		args4
	cmp		r11, 3
	je		args3
	cmp		r11, 2
	je		args2
	cmp		r11, 1
	je		args1
	jmp		args0

	args6:
	mov		r9, [rcx + 48]
	args5:
	mov		r8, [rcx + 40]
	args4:
	mov		r10, [rcx + 32]
	args3:
	mov		rdx, [rcx + 16]
	args2:
	mov		rsi, [rcx + 8]
	args1:
	mov		rdi, [rcx]
	args0:
	syscall
	ret
