.text
.intel_syntax noprefix
.globl pl_syscall

pl_syscall:
	push		rbp
	mov		rbp, rsp

	mov		rax, rdi
	mov		r11, rsi
	mov		rcx, rdx

	args6:
	cmp		r11, 6
	jl		args5
	mov		r9, [rcx + 48]

	args5:
	cmp		r11, 5
	jl		args4
	mov		r8, [rcx + 40]

	args4:
	cmp		r11, 4
	jl		args3
	mov		r10, [rcx + 32]

	args3:
	cmp		r11, 3
	jl		args2
	mov		rdx, [rcx + 16]

	args2:
	cmp		r11, 2
	jl		args1
	mov		rsi, [rcx + 8]

	args1:
	cmp		r11, 1
	jl		args0
	mov		rdi, [rcx + 0]

	args0:
	syscall
	mov		rsp, rbp
	pop		rbp
	ret
