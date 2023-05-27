.text
.intel_syntax noprefix
.globl pl_syscall

pl_syscall:
	push		esp
	mov		eax, [esp + 8]
	mov		ebx, [esp + 16]

	cmp		dword ptr [esp + 12], 6
	je		args6
	cmp		dword ptr [esp + 12], 5
	je		args5
	cmp		dword ptr [esp + 12], 4
	je		args4
	cmp		dword ptr [esp + 12], 3
	je		args3
	cmp		dword ptr [esp + 12], 2
	je		args2
	cmp		dword ptr [esp + 12], 1
	je		args1
	jmp		args0

	args6:
	mov		ebp, [ebx + 20]
	args5:
	mov		edi, [ebx + 16]
	args4:
	mov		esi, [ebx + 12]
	args3:
	mov		edx, [ebx + 8]
	args2:
	mov		ecx, [ebx + 4]
	args1:
	mov		ebx, [ebx]

	args0:
	int 0x80
	pop		esp
	ret
